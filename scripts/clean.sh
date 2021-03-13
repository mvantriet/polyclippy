#!/bin/bash

SCRIPT_DIR=$(dirname "$0")
ROOT_DIR="$SCRIPT_DIR/../"
echo "Cleaning up"
rm -rf $ROOT_DIR/dist $ROOT_DIR/build