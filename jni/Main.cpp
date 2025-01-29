#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "fstream"
#include "iostream"
#include "stdio.h"
#include "Includes/obfuscate.h"
#include "Oxorany/oxorany.h"
#include "KittyMemory/MemoryPatch.h"
#include "Substrate/CydiaSubstrate.h"
#include "Includes/Logger.h"
#include "Includes/Utils.h"
#include "Includes/Macros.h"
#include "Includes.h"
using namespace std;
#define anogs OBFUSCATE("libil2cpp.so")

int sub_38fddc4(int damage) {
	return 99999;
	}

void *hook_thread(void *) {
    while (!isLibraryLoaded(OBFUSCATE("libil2cpp.so"))) {
        sleep(1);
    }
    HOOK_LIB_NO_ORIG("libil2cpp.so", "0x38fddc4", sub_38fddc4);
    return NULL;
}

__attribute__((constructor)) void _HookRunning() {
    pthread_t ptid;
    pthread_create(&ptid, NULL, hook_thread, NULL);
}

