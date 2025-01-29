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

echo "${G}===> ${N}Native Development Kit Clean..."
echo "${G}===> ${N}Please wait a moments..."

START_TIME=$(date +%s)

$NDK_ROOT/ndk-build clean

if [ $? -eq 0 ]; then
	echo "${G}===> ${N}NDK Clean Succeed!"
else
	echo "${G}===> ${N}ERROR! NDK Clean Failed!"
	exit 1
fi

END_TIME=$(date +%s)
BUILD_TIME=$((END_TIME - START_TIME))
echo "${G}CLEANING NDK PROJECT COMPLETE in ${N}${BUILD_TIME}s"