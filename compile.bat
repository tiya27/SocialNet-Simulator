@echo off
REM ============================================
REM  Social Network Project - COL106 Assignment
REM  Compile script for Windows
REM ============================================

echo Compiling Social Network project...

g++ -std=c++17 -Wall -O2 main.cpp -o main.exe
if %errorlevel% neq 0 (
    echo Compilation failed!
    exit /b 1
) else (
    echo Compilation successful. Run main.exe to start.
)
