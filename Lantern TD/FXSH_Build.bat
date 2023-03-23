@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.


if exist LANTERNT.G1A  del LANTERNT.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"D:\360MoveData\Users\hasee\Desktop\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"D:\360MoveData\Users\hasee\Desktop\Tools\MakeAddinHeader363.exe" "D:\c++learning\Lantern TD"
if not exist LANTERNT.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

