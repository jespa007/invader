call dpp mapa1.cc


@echo off
CLS

:1

 BANNER MUNTANT
 ECHO.
 BANNER %1

 tcc -mh -1 -IInclude -LLib -eEXE\DAT\mapa1.exe mapa1.obj > error.mnt
 if errorlevel 1 goto ERROR2
 CLS
 ECHO Sense errors. 
 goto end

:ERROR2
 CLS
 BANNER ERR.MNT:
 ECHO.
 type2 error.mnt
 goto end

:end

cd exe\dat
del mapa1.dat
mapa1
cd ..
cd ..
