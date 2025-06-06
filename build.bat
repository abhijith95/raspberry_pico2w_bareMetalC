@echo off
SETLOCAL EnableDelayedExpansion

cls

rmdir build /q /s
mkdir build

if [%~1] == [] (
    echo Error no application input is found
    exit /b 1
)

cmake -S . -B build/ -DAPPL_TO_BUILD=%~1 -G "Ninja" -DCMAKE_BUILD_TYPE=Debug

cmake --build build/