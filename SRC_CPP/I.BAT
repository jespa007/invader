@echo off

CLS

:1
 echo.
 echo COMPILANT INVADER.CPP
echo.
 tcc -P -mh -1 -c SRC\INVADER.CPP -o BUILD\INVADER.OBJ > BUILD\RESULT.CMP
 if errorlevel 1 goto ERROR1
 CLS
 GOTO MOUNT

:ERROR1
 CLS
 echo ERRORS:
 ECHO.
 type BUILD\RESULT.CMP
 goto end

:MOUNT
CLS

echo.
echo MUNTANT %1
echo.

 tcc -P -mh -1 -eBIN\INVADER.EXE BUILD\INVADER.OBJ > RESULT.MNT
 if errorlevel 1 goto ERROR2
 CLS
 ECHO Sense errors. 
 goto end

:ERROR2
 CLS
 echo ERR.MNT:
 ECHO.
 type BUILD\ERROR.MNT
 goto end


:end