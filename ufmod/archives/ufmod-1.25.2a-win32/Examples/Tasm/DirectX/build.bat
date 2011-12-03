@echo off
rem Set compiler location:
SET TASM=\tasm

if not exist "%TASM%\bin\tasm32.exe" goto Err1
if not exist "%TASM%\lib\imp32i.lib" goto Err2
"%TASM%\bin\tasm32" /mx /m4 mini_ds.asm
"%TASM%\bin\tlink32" /aa /x /B:0x400000 mini_ds.obj dsufmod.lib, mini_ds.exe,, "%TASM%\lib\imp32i.lib"
del mini_ds.obj
goto TheEnd
:Err1
echo Couldn't find tasm32.exe in %TASM%\bin
got TheEnd
:Err2
echo Couldn't find imp32i.lib in %TASM%\lib
:TheEnd
pause
cls
