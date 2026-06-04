@echo off

CLS

:1
 
 echo COMPILANT
 ECHO.
 echo TEST.C
 tcc  -mh -1 -IInclude -LLib -c *.C > error.cmp
 if errorlevel 1 goto ERROR1
 CLS
 GOTO MOUNT

:ERROR1
 CLS
 echo ERR.CMP:
 ECHO.
 type error.cmp
 goto end

:MOUNT

if errorlevel 1 goto end

if EXIST pastaman.obj del pastaman.obj

doc test

:end
