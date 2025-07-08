#!/bin/bash

BUILD_DIR="build"

if command -v gcc-13 &>/dev/null && command -v g++-13 &>/dev/null; then
    export CC=gcc-13
    export CXX=g++-13
else
    export CC=gcc
    export CXX=g++
fi
mkdir -p $BUILD_DIR

echo "Configuring the project..."
cmake -B $BUILD_DIR -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

echo "Building the project..."
cmake --build $BUILD_DIR --target all
cmake --build build --target my_plugins

if [ $? -eq 0 ]; then
    echo "Build completed successfully."
else
    echo "Build failed. Please check the errors."
    exit 1
fi
