@ECHO OFF
IF EXIST *.obj (DEL *.obj)
IF EXIST *.ilk (DEL *.ilk)
IF EXIST *.pdb (DEL *.pdb)
IF EXIST *.exe (DEL *.exe)

REM cl /nologo /Zi /GR- /EHs /W4 /MDd /D _CRT_SECURE_NO_WARNINGS -I ..\include -I ..\deps\esat\include /c ..\src\bmp.cc
REM cl /nologo /Zi /GR- /EHs /W4 /MDd /D _CRT_SECURE_NO_WARNINGS -I ..\include -I ..\deps\esat\include /c ..\src\threads_example.cc
REM cl /nologo /Zi /GR- /EHs /W4 /MDd /Fe:threads_example_d.exe *.obj ..\deps\esat\bin\ESAT_d.lib opengl32.lib user32.lib gdi32.lib shell32.lib /link /IGNORE:4099

cl /nologo /O2 /GR- /EHs /W3 /MD /D _CRT_SECURE_NO_WARNINGS /c -I ..\include -I ..\deps\esat\include /c ..\src\bmp.cc
cl /nologo /O2 /GR- /EHs /W3 /MD /D _CRT_SECURE_NO_WARNINGS /c -I ..\include -I ..\deps\esat\include /c ..\src\threads_example.cc
cl /nologo /O2 /GR- /EHs /W3 /MD /Fe:threads_example.exe *.obj ..\deps\esat\bin\ESAT.lib opengl32.lib user32.lib gdi32.lib shell32.lib

IF EXIST *.obj (DEL *.obj)
IF EXIST *.ilk (DEL *.ilk)
IF EXIST *.pdb (DEL *.pdb)
IF EXIST *.exe (MOVE *.exe ..\bin)