#!/bin/bash

SCRIPT_DIR=$(dirname "$0")
if [ ! $# -ge 2 ]; then
    echo "Please provide 2 arguments :: <platform:darwin|linux> <build_type:release|debug>"
    exit 1
fi
$SCRIPT_DIR/clean.sh
$SCRIPT_DIR/build.sh $@ false all