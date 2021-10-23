@echo off
cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/main.cc
cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/ball.cc
cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/brick.cc
cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/definitions.cc
cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/platform.cc
cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/game.cc

cl /nologo /Zi /MDd /EHs /W1 /Fe:main.exe main.obj ball.obj brick.obj definitions.obj platform.obj game.obj ../deps/sfml/x86/lib/sfml-system-s-d.lib ../deps/sfml/x86/lib/sfml-window-s-d.lib ../deps/sfml/x86/lib/sfml-graphics-s-d.lib ../deps/sfml/x86/lib/freetype.lib winmm.lib opengl32.lib shell32.lib gdi32.lib user32.lib advapi32.lib

IF EXIST %~dp0*.obj (DEL "%~dp0*.obj")
IF EXIST %~dp0*.ilk (DEL "%~dp0*.ilk")
IF EXIST %~dp0*.pdb  (DEL "%~dp0*.pdb")
IF EXIST %~dp0main.exe  (MOVE %~dp0main.exe %~dp0..\bin)