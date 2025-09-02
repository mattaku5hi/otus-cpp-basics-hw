#!/bin/bash
set -e
set -u

curdir=$(pwd)
builddir="$(pwd)/debug"
rm -rf $builddir
cmake -DCMAKE_BUILD_TYPE=Debug -B $builddir
make -j$(nproc) -C $builddir