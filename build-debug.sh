#!/bin/sh

TEMP_BUILD_DIR=~/temp/build/TRC2PMBUSTool/Debug

if [  ! -e $TEMP_BUILD_DIR ]; then
mkdir $TEMP_BUILD_DIR
fi

cmake -H. -B$TEMP_BUILD_DIR -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"

cmake --build $TEMP_BUILD_DIR
