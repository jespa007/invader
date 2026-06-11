@echo off


CLS

:1
 
 echo COMPILANT
 ECHO.
 echo INVADER.C

 c:\tc3\bin\tcc -P -mh -1 -Ic:\tc3\Include -Lc:\tc3\Lib -c invader.cpp > error.cmp
 if errorlevel 1 goto ERROR1
 if errorlevel 2 goto WARNING1
 CLS
 GOTO MOUNT

:WARNING1
CLS
echo WARNINGS:
ECHO.
echo type error.cmp
goto end


:ERROR1
 CLS
 echo ERRORS:
 ECHO.
 type error.cmp
 goto end

:MOUNT

if errorlevel 1 goto end

if EXIST test.obj del test.obj
if EXIST pastaman.obj del pastaman.obj
del mapa1.obj
del mapa2.obj
del mapa3.obj
del intro.obj
del credits.obj
del proba1.obj
del genmov.obj

doc INVADER.EXE

:end