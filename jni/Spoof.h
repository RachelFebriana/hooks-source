#include "Includes.h"
#include "Tools.h"
#include "fake_dlfcn.h"
#include "plthook.h"

// ============================================================================================= //
const char *namesToHide[] = {"libPutrimod.so"};

const char *isNameInBlackList(const char *in) {
    if (!in)
        return 0;

    for (int i = 0; i < (sizeof(namesToHide) / sizeof(namesToHide[0])); i++) {
        const char *found = strstr(in, namesToHide[i]);
        if (found) {
            return found;
        }
    }
    return 0;
}

char pkgName[64];

// ============================================================================================= //
int _open(const char *pathname, int flags, mode_t mode) {
    if (isNameInBlackList(pathname)) {
        return -1;
    }

    if (strstr(pathname, pkgName)) {
        if (strstr(pathname, ".apk")) {
            std::string s = "/data/data/";
            s += pkgName;
            s += "/lib/libtia.so";
            pathname = s.c_str();
        }
    }

    return open(pathname, flags, mode);
}

int _creat(const char *pathname, int flags) {
    if (isNameInBlackList(pathname)) {
        return -1;
    }

    if (strstr(pathname, pkgName)) {
        if (strstr(pathname, ".apk")) {
            std::string s = "/data/data/";
            s += pkgName;
            s += "/lib/libtia.so";
            pathname = s.c_str();
        }
    }

    return creat(pathname, flags);
}

// ============================================================================================= //
FILE *_fopen(const char *pathname, const char *mode) {
    if (isNameInBlackList(pathname)) {
        return 0;
    }

    if (strstr(pathname, pkgName)) {
        if (strstr(pathname, ".apk")) {
            std::string s = "/data/data/";
            s += pkgName;
            s += "/lib/libtia.so";
            pathname = s.c_str();
        }
    }

    return fopen(pathname, mode);
}

// ============================================================================================= //
ssize_t _read(int fd, void *buf, size_t count) {
    auto result = read(fd, buf, count);

    if (result > 0) {
        uint8_t *buff = (uint8_t *) buf;
        for (int i = 0; i < result; i++) {
            for (int j = 0; j < (sizeof(namesToHide) / sizeof(namesToHide[0])); j++) {
                auto name = namesToHide[j];
                if (i <= (result - strlen(name))) {
                    if (memcmp(&buff[i], name, strlen(name)) == 0) {
                        memset(&buff[i], '.', strlen(name));
                    }
                }
            }
        }
    }
    return result;
}

// ============================================================================================= //
size_t _fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    auto result = fread(ptr, size, nmemb, stream);

    if (result > 0) {
        uint8_t *buff = (uint8_t *) ptr;
        for (int i = 0; i < result; i++) {
            for (int j = 0; j < (sizeof(namesToHide) / sizeof(namesToHide[0])); j++) {
                auto name = namesToHide[j];
                if (i <= (result - strlen(name))) {
                    if (memcmp(&buff[i], name, strlen(name)) == 0) {
                        memset(&buff[i], '.', strlen(name));
                    }
                }
            }
        }
    }

    return result;
}

// ============================================================================================= //
int _access(const char *pathname, int mode) {
    if (isNameInBlackList(pathname)) {
        return -1;
    }

    if (strstr(pathname, pkgName)) {
        if (strstr(pathname, ".apk")) {
            std::string s = "/data/data/";
            s += pkgName;
            s += "/lib/libtia.so";
            pathname = s.c_str();
        }
    }

    return access(pathname, mode);
}

// ============================================================================================= //
int _stat(const char *pathname, struct stat *statbuf) {
    if (isNameInBlackList(pathname)) {
        return -1;
    }

    if (strstr(pathname, pkgName)) {
        if (strstr(pathname, ".apk")) {
            std::string s = "/data/data/";
            s += pkgName;
            s += "/lib/libtia.so";
            pathname = s.c_str();
        }
    }

    return stat(pathname, statbuf);
}

int _lstat(const char *pathname, struct stat *statbuf) {
    if (isNameInBlackList(pathname)) {
        return -1;
    }

    if (strstr(pathname, pkgName)) {
        if (strstr(pathname, ".apk")) {
            std::string s = "/data/data/";
            s += pkgName;
            s += "/lib/libtia.so";
            pathname = s.c_str();
        }
    }

    return lstat(pathname, statbuf);
}

// ============================================================================================= //
char *_fgets(char *dest, int size, FILE *stream) {
    auto ret = fgets(dest, size, stream);
    check:
    if (ret) {
        if (isNameInBlackList(ret)) {
            ret = fgets(dest, size, stream);
            goto check;
        }
    }

    return ret;
}

// ============================================================================================= //
DIR *_opendir(const char *name) {
    if (isNameInBlackList(name)) {
        return 0;
    }
    return opendir(name);
}

struct dirent *_readdir(DIR *dirp) {
    auto ret = readdir(dirp);
    check:
    if (ret) {
        if (isNameInBlackList(ret->d_name)) {
            ret = readdir(dirp);
            goto check;
        }
    }
    return ret;
}

// ============================================================================================= //
void *tersafe_thread(void *) {
    auto tersafe = Tools::GetBaseAddress("libtersafe.so");
    while (!tersafe) {
        tersafe = Tools::GetBaseAddress("libtersafe.so");
        sleep(1);
    }

    plthook_t *plthook;
    if (plthook_open(&plthook, "libtersafe.so") == 0) {
        plthook_replace(plthook, "open", (void *) _open, NULL);
        plthook_replace(plthook, "creat", (void *) _creat, NULL);
        plthook_replace(plthook, "read", (void *) _read, NULL);
        plthook_replace(plthook, "access", (void *) _access, NULL);
        plthook_replace(plthook, "stat", (void *) _stat, NULL);
        plthook_replace(plthook, "lstat", (void *) _lstat, NULL);
        plthook_replace(plthook, "fopen", (void *) _fopen, NULL);
        plthook_replace(plthook, "fread", (void *) _fread, NULL);
        plthook_replace(plthook, "fgets", (void *) _fgets, NULL);
        plthook_replace(plthook, "opendir", (void *) _opendir, NULL);
        plthook_replace(plthook, "readdir", (void *) _readdir, NULL);
        plthook_close(plthook);
    }

    auto result = Tools::FindPattern("libtersafe.so", "07 49 79 44 08 60 07 48");
    if (result) {
        auto addr = result;
        while (true) {
            if (*(uint8_t*)(addr-2) == 0xC0 || *(uint8_t*)(addr-1) == 0x46) {
                break;
            } else addr++;
        }
        auto syscall_table = *(uintptr_t *) (addr) + result + 0x6;

        while (true) {
            *(uint32_t *) (syscall_table) = 0;
            sleep(1);
        }
    }

    return 0;
}

// ============================================================================================= //
void startHook() {
    FILE *f = fopen("/proc/self/cmdline", "r");
    if (f) {
        fgets(pkgName, sizeof pkgName, f);
        fclose(f);

        for(int i = 0; i < strlen(pkgName); i++) {
            if (pkgName[i] == ':') {
                pkgName[i] = '\0';
                break;
            }
        }
    }

    pthread_t t;
    pthread_create(&t, 0, tersafe_thread, 0);
}

