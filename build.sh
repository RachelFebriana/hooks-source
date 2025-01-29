#!/bin/bash

clear

R='\033[0;31m'
G='\033[0;32m'
Y='\033[0;33m'
C='\033[0;36m'
P='\033[0;35m'
N='\033[0m'

NDK_ROOT=/data/data/com.aide.ui/no_backup/ndksupport-1710240003/android-ndk-aide
NDK_PROJECT_PATH=jni/main.cpp
NDK_APPLICATION_MK=jni/Application.mk
ARCH_TARGETS="armeabi-v7a arm64-v8a"

echo "${G}===> ${N}Native Development Kit Build..."
echo "${G}===> ${N}Please wait a moments..."

NDK_VERSION=$($NDK_ROOT/ndk-build --version)
echo "${G}===> ${P}[*] NDK Version ${N}$NDK_VERSION"

START_TIME=$(date +%s)

for ARCH_TARGET in ${ARCH_TARGETS}
do
    echo "${G}===> ${P}[*] Build Arch ABI ${N}${ARCH_TARGET}"
    
    TARGET_MIN_API=$(grep "APP_PLATFORM" $NDK_APPLICATION_MK | cut -d'=' -f2)

    echo "${G}===> ${P}[*] Build Min API ${N}$TARGET_MIN_API"

    if grep -q "APP_OPTIM := release" $NDK_APPLICATION_MK; then
        BUILD_TYPE="Release"
    else
        BUILD_TYPE="Debug"
    fi

    echo "${G}===> ${P}[*] Build Type ${N}$BUILD_TYPE"

    $NDK_ROOT/ndk-build -j$(nproc)

    if [ $? -eq 0 ]; then
        echo "${G}===> ${N}NDK Build Succeed!"
    else
        echo "${G}===> ${N}ERROR! NDK Build Failed!"
        exit 1
    fi
done

END_TIME=$(date +%s)
BUILD_TIME=$((END_TIME - START_TIME))
echo "${G}BUILD COMPLETE in ${N}${BUILD_TIME}s"