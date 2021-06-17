@echo off

echo [PMK5]: (cfg 'space-reset.lua) (architecture 'x86') (gmake2)
pmk5 --file=space_reset.lua gmake2
echo [PMK5]: Terminated