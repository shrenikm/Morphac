#!/bin/bash

usage="$(basename "$0") [-h] [command]

options:
    -h      Help text
    clean         Cleans the project build directory
    build         Builds the project using CMake
    install       Builds and installs the project using CMake
    cleanbuild    Cleans the project and builds it again"

while getopts 'h' option; do
    case "$option" in
        h) echo "$usage"
           exit
           ;;
    esac
done

# At least one argument needs to be passed.
if [ $# -eq 0 ]
then
    echo "The script needs at least one argument. See the usage with -h"
fi

if [[ $1 = "clean" ]]
then
    echo "Cleaning the build directory ..."
    rm -rf build/*
elif [[ $1 = "build" ]]
then
    echo "Building the project ..."
    cd build
    # TODO: Add Cmake -D options here.
    cmake ..
elif [[ $1 = "install" ]]
then
    echo "Building the project ..."
    cd build
    cmake ..
    echo "Installing the project ..."
    make install
elif [[ $1 = "cleanbuild" ]]
then
    echo "Cleaning the build directory ..."
    rm -rf build/*
    echo "Building the project ..."
    cd build
    cmake ..
    echo "Installing the project ..."
    make install

else
    echo "Invalid option. See the usage with -h"
    exit 1
fi