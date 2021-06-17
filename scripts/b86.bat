@echo off

echo [BUILD/RESET]: Initializing Build
make CC=gcc config=debug_x86 RESET
echo [BUILD/RESET]: Build Terminated