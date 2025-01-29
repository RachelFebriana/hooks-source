#!/bin/bash
ACHEL=ndk
RACHELDIR=ARCHDIR
cyan="\033[96m"
green="\033[92m"
red="\033[91m"
blue="\033[94m"
yellow="\033[93m"
white='\033[0m'

function clear() {
echo -e "\n"
echo -e "$red Clear Log Libs , Obj \n$white"
echo -e "\n"
}
function install() {
if [ -d $pwd../ndk ] ; then
echo -e "\n$green Install Android Kit (Ndk) \n"
else
echo -e "\n$red Ndk Kit Android Not Found...! \n"
sleep 3
echo -e "\n$green Waiting Download Ndk Android kit...\n$white"
wget https://dl.google.com/android/repository/android-ndk-r27c-linux.zip
sleep 3
echo -e "\n$yellow Unzip File Ndk Wait.... \n"
sleep 5
unzip  android-ndk-r27c-linux.zip
sleep 3
echo -e "\n$red Clear Zip Android Ndk \n"
sleep 3
mv android-ndk-r27c $ACHEL
sleep 3
rm -rf android-ndk-r27c-linux.zip
fi
}
clear
install
