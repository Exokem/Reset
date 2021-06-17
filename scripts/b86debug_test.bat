@echo off

echo [DEBUG/RTEST]: Initializing RTEST Debug
cd bin/RTEST/Debug_x86
gdb RTEST.exe
echo [DEBUG/RTEST]: RTEST Debug Terminated