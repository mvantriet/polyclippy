#!/bin/bash

PLATFORM=$1
BUILD_TYPE=$2
BUILD_TARGET=$3
PROJECT_NAME=polyclippy

SCRIPT_DIR=$(dirname "$0")
ROOT_DIR="$SCRIPT_DIR/../"
if [ ! $# -ge 2 ]; then
    echo "Please provide 2 arguments :: <platform:darwin|linux> <build_type:release|debug>"
    exit 1
fi
# Ensure the project is build
$SCRIPT_DIR/build.sh $@ true all
(cd build/$PROJECT_NAME/$PLATFORM && ctest)