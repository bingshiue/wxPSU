#!/bin/sh

TEMP_BUILD_DIR=~/temp/build/TRC2PMBUSTool/Release

if [  ! -e $TEMP_BUILD_DIR ]; then
mkdir $TEMP_BUILD_DIR
fi

cmake -H. -B$TEMP_BUILD_DIR -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"

cmake --build $TEMP_BUILD_DIR
