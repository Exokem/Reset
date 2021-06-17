@echo off
echo Executing premake5 gmake2; configuration 'space-reset.lua'
pmk5 --file=space_reset.lua gmake2
echo Executing final build
make config=debug_x32
echo Process finished
PAUSE