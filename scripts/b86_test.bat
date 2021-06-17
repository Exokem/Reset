@echo off

echo [BUILD/RTEST]: Initializing Build
make CC=gcc config=debug_x86 RTEST
echo [BUILD/RTEST]: Build Terminated
