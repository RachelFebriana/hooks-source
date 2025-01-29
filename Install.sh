#!/bin/bash
ACHEL=ndk
RACHELDIR=ARCHDIR
echo "Install Ndk Android"
wget https://dl.google.com/android/repository/android-ndk-r27c-linux.zip
sleep 5
echo "Unzip Ndk File "
unzip android-ndk-r27c-linux.zip
mv  android-ndk-r27 $ACHEL
sleep 3
echo "cleannn Build"
rm -rf android-ndk-r27c-linux.zip
sleep 2
touch log.txt
