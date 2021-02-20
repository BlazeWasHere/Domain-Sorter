#!/usr/bin/env bash

if [ -d "sorted" ]; then
    echo "Folder 'sorted' exists, clearing the folder..."
    rm -rf sorted/
fi

echo "Creating 'sorted' folder"    
mkdir sorted/

if [ ! -f main ]; then
    echo "Compiled bin not found, attempting to compile..."

    if [ ! command -v g++ &> /dev/null ]; then
        echo "g++ not found in PATH. Exiting!"
        exit
    fi

    if [ ! -f main.cpp ]; then
        echo "main.cpp not found in folder. Exiting!"
        exit
    fi

    g++ -o main main.cpp -O3
fi

echo "Starting..."
./main "$@"