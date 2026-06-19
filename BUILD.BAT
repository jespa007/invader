@echo off

CLS

IF NOT EXIST BUILD MKDIR BUILD

:1
 echo COMPILANT EFFECTS.CPP
tcc -P -mh -1 -ISRC -nBUILD -c SRC\EFFECTS.CXX > BUILD\ERROR.CMP
 if errorlevel 1 goto ERROR1
 echo COMPILANT ENEMICS.CXX
tcc -P -mh -1 -ISRC -nBUILD -c SRC\ENEMICS.CC  > BUILD\ERROR.CMP
if errorlevel 1 goto ERROR1
 echo COMPILANT FONT.CXX
tcc -P -mh -1 -ISRC -nBUILD -c SRC\FONT.CXX  > BUILD\ERROR.CMP
if errorlevel 1 goto ERROR1
 echo COMPILANT GRAFICS.CXX
tcc -P -mh -1 -ISRC -nBUILD -c SRC\GRAFICS.CXX > BUILD\ERROR.CMP
if errorlevel 1 goto ERROR1
 echo COMPILANT MODEX.CXX
tcc -P -mh -1 -ISRC -nBUILD -c SRC\MODEX.CXX > BUILD\ERROR.CMP
if errorlevel 1 goto ERROR1
 echo COMPILANT MOUSE.CXX
tcc -P -mh -1 -ISRC -nBUILD -c SRC\MOUSE.CXX > BUILD\ERROR.CMP
if errorlevel 1 goto ERROR1
 echo COMPILANT PALETA.CXX
tcc -P -mh -1 -ISRC -nBUILD -c SRC\PALETA.CXX > BUILD\ERROR.CMP
if errorlevel 1 goto ERROR1
 echo COMPILANT PCX.CXX
tcc -P -mh -1 -ISRC -nBUILD -c SRC\PCX.CXX > BUILD\ERROR.CMP
if errorlevel 1 goto ERROR1
 echo COMPILANT SPRITES.CXX
tcc -P -mh -1 -ISRC -nBUILD -c SRC\SPRITES.CXX > BUILD\ERROR.CMP
if errorlevel 1 goto ERROR1
 echo COMPILANT VGAREGS.CXX
tcc -P -mh -1 -ISRC -nBUILD -c SRC\VGAREGS.CXX > BUILD\ERROR.CMP
if errorlevel 1 goto ERROR1
 echo COMPILANT VSCREEN.CXX
tcc -P -mh -1 -ISRC -nBUILD -c SRC\VSCREEN.CXX > BUILD\ERROR.CMP
 if errorlevel 1 goto ERROR1
 echo COMPILANT UTIL.CXX
tcc -P -mh -1 -ISRC -nBUILD -c SRC\UTIL.CXX > BUILD\ERROR.CMP
 if errorlevel 1 goto ERROR1
 echo COMPILANT INVADER.CPP
 tcc -P -mh -1 -ISRC -nBUILD -c SRC\INVADER.CPP > BUILD\ERROR.CMP
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

 tcc -P -mh -1 -eBIN\INVADER.EXE BUILD\*.OBJ > BUILD\ERROR.MNT
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