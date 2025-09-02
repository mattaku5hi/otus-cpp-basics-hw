#!/bin/bash
set -e
set -u

curdir=$(pwd)
builddir="$(pwd)/release"
rm -rf $builddir
cmake -DCMAKE_BUILD_TYPE=Release -B $builddir
make -j$(nproc) -C $builddir