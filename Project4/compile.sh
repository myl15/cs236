#!/bin/bash

if [ $# -eq 0 ];
then
    echo "$0: Missing arguments"
    exit 1
fi
if [ $1 == "Compile" ];
then
    g++ -Wall -Werror -std=c++17 -g *.cpp -o main
    ./main.exe $2
elif [ $1 == "Zip" ];
then   
    zip $2.zip *.cpp *.h
fi

echo "Process complete"