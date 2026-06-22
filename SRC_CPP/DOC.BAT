@echo off
CLS

:1
echo.
echo MUNTANT %1
echo.

 c:\tc3\bin\tcc -P -mh -1 -Ic:\tc3\Include -Lc:\tc3\Lib -e..\BIN\%1 *.OBJ > error.mnt
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
