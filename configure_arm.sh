#!/bin/bash
mkdir build

cd build
chmod +x ../cmake/x11/bin/cmake
../cmake/x11/bin/cmake -D ARM=1 -G "Unix Makefiles" --build ../

make && make install
