DEL *.OBJ

call dcc BIGFNT.c
pause
call doc BIGFNT.exe
pause
BIGFNT

del *.obj

call dcc MEDFNT.c
pause
call doc MEDFNT.exe
pause
MEDFNT

del *.obj



call dcc FONTMT.c
pause
call doc FONTMT.exe
pause
FONTMT


move *.raw c:\pastaman\exe\grafics


