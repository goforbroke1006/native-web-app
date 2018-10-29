#!/usr/bin/env bash

cd test
cmake -H. -Bcmake-build-debug
cd cmake-build-debug
cmake --build .
#ctest
make test