call dpp credits.cc

pause
del mapa1.obj
del invader.obj
del test.obj
del intro.obj 

@echo off
CLS

:1

 BANNER MUNTANT
 ECHO.
 BANNER %1

 tcc -mh -1 -I%Include_Dir% -L%Lib_Dir% -e..\EXE\DAT\credits.exe credits.obj > error.mnt
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


cd ..\exe\dat
del credits.dat
credits
cd ..
cd ..
cd ver1.01
