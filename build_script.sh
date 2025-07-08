#!/bin/bash

BUILD_DIR="build"

mkdir -p $BUILD_DIR

echo "Configuring the project..."
cmake -B $BUILD_DIR -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

echo "Building the project..."
cmake --build $BUILD_DIR --target all

if [ $? -eq 0 ]; then
    echo "Build completed successfully."
else
    echo "Build failed. Please check the errors."
    exit 1
fi
