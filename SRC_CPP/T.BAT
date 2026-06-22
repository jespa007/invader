@echo off

CLS

:1
 
 BANNER COMPILANT
 ECHO.
 BANNER TEST.C
 tcc  -mh -1 -IInclude -LLib -c *.C > error.cmp
 if errorlevel 1 goto ERROR1
 CLS
 GOTO MOUNT

:ERROR1
 CLS
 BANNER ERR.CMP:
 ECHO.
 type2 error.cmp
 goto end

:MOUNT

if errorlevel 1 goto end

if EXIST pastaman.obj del pastaman.obj

doc test

:end
