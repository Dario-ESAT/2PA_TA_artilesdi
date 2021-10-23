@echo off

del *.obj *.pdb

clang-cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -m32 -I../include -I../deps/sfml/x86/include ../src/main.cc

clang-cl /nologo /Zi /MDd /W4 /Fetest.exe -m32 main.obj ../deps/sfml/x86/lib/sfml-system-s-d.lib ../deps/sfml/x86/lib/sfml-window-s-d.lib ../deps/sfml/x86/lib/sfml-graphics-s-d.lib ../deps/sfml/x86/lib/freetype.lib winmm.lib opengl32.lib shell32.lib gdi32.lib user32.lib advapi32.lib
