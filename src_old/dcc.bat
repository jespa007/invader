@echo off
CLS

if EXIST %1 goto 1
echo No input files.
goto end

:1
 
 echo COMPILANT
 ECHO.
 echo %1
 tcc  -mh -2 -IInclude -LLib -c %1 > error.cmp
 if errorlevel 1 goto ERROR1
 CLS
 ECHO Sense errors.
 goto end

:ERROR1
 CLS
 echo ERR.CMP:
 ECHO.
 type2 error.cmp
 goto end

:end
