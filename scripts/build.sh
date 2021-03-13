#!/bin/bash

PLATFORM=$1
BUILD_TYPE=$2
RUN_TESTS=$3
BUILD_TARGET=$4

SCRIPT_DIR=$(dirname "$0")
ROOT_DIR="$SCRIPT_DIR/../"
if [ ! $# -eq 4 ]; then
    echo "Please provide 4 arguments :: <platform:darwin|linux> <build_type:release|debug> <include_test:true|false> <make_target:all|install>"
    exit 1
fi

PROJECT_NAME=polyclippy
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++\
    -D RUN_TESTS=$RUN_TESTS -H. -B$ROOT_DIR/build/$PROJECT_NAME/$PLATFORM
(cd $ROOT_DIR/build/$PROJECT_NAME/$PLATFORM && make $BUILD_TARGET)
