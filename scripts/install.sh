#!/bin/bash
if (( $EUID != 0 )); then
    echo "Only root can install lib, please use sudo"
    exit
fi
if [ ! $# -ge 2 ]; then
    echo "Please provide 2 arguments :: <platform:darwin|linux> <build_type:release|debug>"
    exit 1
fi
SCRIPT_DIR=$(dirname "$0")
$SCRIPT_DIR/build.sh $@ false install
