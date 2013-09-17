@echo off

set BINARY=%1
set TITLE=%2
set PLATFORM=%3

rem Set path so we find the sqlite3xx.dll (don't copy it around! linker paths are absolute!)
set PATH=..\src;%PATH%

%BINARY% >%BINARY.RES
if ERRORLEVEL == 1 goto :ERROR
echo %BINARY%: %TITLE% .. OK
goto END

:ERROR
echo %BINARY%: %TITLE% .. ERROR
:END

rem TODO: find a way to do this with things provided by the system
rem diff $BINARY.MUST $BINARY.RES > $BINARY.DIFF && printf "OK\n" || printf "ERROR\n"
