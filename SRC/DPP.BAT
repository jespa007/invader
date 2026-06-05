@echo off
CLS

if EXIST %1 goto 1
echo No input files.
goto end

:1
 
 BANNER COMPILANT
 ECHO.
 BANNER %1
 tcc  -P -mh -1 -I%INCLUDE_DIR% -L%LIB_DIR% -c %1 > error.cmp
 if errorlevel 1 goto ERROR1
 CLS
 ECHO Sense errors.
 goto end

:ERROR1
 CLS
 BANNER ERR.CMP:
 ECHO.
 type2 error.cmp
 goto end

:end
