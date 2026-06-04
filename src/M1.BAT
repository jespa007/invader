call dpp mapa1.cc


@echo off
CLS

:1

 echo MUNTANT
 ECHO.
 echo %1

 tcc -mh -1 -IInclude -LLib -e..\bin\DAT\mapa1.exe mapa1.obj > error.mnt
 if errorlevel 1 goto ERROR2
 CLS
 ECHO Sense errors. 
 goto end

:ERROR2
 CLS
 echo ERR.MNT:
 ECHO.
 type error.mnt
 goto end

:end

cd ..\bin\dat
del mapa1.dat
mapa1
cd ..
cd ..

