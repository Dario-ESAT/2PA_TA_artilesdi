@echo Compilando...
@echo off

cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../deps/imgui -I ../deps/sfml/x86/include ../deps/imgui/*.cpp

cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../deps/imgui -I ../deps/sfml/x86/include -I ../deps/imgui-sfml ../deps/imgui-sfml/*.cpp

cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c ../deps/sqlite3/sqlite3.c

cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../include -I ../deps/imgui-sfml -I ../deps/sfml/x86/include -I ../deps/sqlite3 -I ../deps/imgui ../src/main.cc
cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../include -I ../deps/imgui-sfml -I ../deps/sfml/x86/include -I ../deps/sqlite3 -I ../deps/imgui ../src/column.cc
cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../include -I ../deps/imgui-sfml -I ../deps/sfml/x86/include -I ../deps/sqlite3 -I ../deps/imgui ../src/database.cc
cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../include -I ../deps/imgui-sfml -I ../deps/sfml/x86/include -I ../deps/sqlite3 -I ../deps/imgui ../src/row.cc
cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../include -I ../deps/imgui-sfml -I ../deps/sfml/x86/include -I ../deps/sqlite3 -I ../deps/imgui ../src/table.cc


cl /nologo /Zi /MDd /EHs /W1 /Fe:main.exe main.obj imgui*.obj sqlite3.obj column.obj database.obj row.obj table.obj  ../deps/sfml/x86/lib/sfml-system-s-d.lib ../deps/sfml/x86/lib/sfml-window-s-d.lib ../deps/sfml/x86/lib/sfml-graphics-s-d.lib ../deps/sfml/x86/lib/freetype.lib winmm.lib opengl32.lib shell32.lib gdi32.lib user32.lib advapi32.lib



@REM ---- sqlite consola ----

@REM cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c ../deps/sqlite3/sqlite3.c

@REM cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../deps/sqlite3 ../src/tipos.cc
@REM cl /nologo /Zi /MDd /EHs /W1 /Fe:tipos.exe sqlite3.obj tipos.obj

@REM cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../deps/sqlite3 ../src/nombre_tablas.cc
@REM cl /nologo /Zi /MDd /EHs /W1 /Fe:nombre_tablas.exe sqlite3.obj nombre_tablas.obj




@REM ---- imgui_pruebas ---

@REM cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../deps/imgui -I ../deps/sfml/x86/include ../deps/imgui/*.cpp
@REM cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../deps/imgui -I ../deps/sfml/x86/include -I ../deps/imgui-sfml ../deps/imgui-sfml/*.cpp

@REM cl /nologo /Zi /MDd /EHs /W1 /DSFML_STATIC /c -I ../include -I ../deps/imgui-sfml -I ../deps/sfml/x86/include -I ../deps/imgui ../src/imgui_pruebas.cc
@REM cl /nologo /Zi /MDd /EHs /W1 /Fe:imgui_pruebas.exe *.obj ../deps/sfml/x86/lib/sfml-system-s-d.lib ../deps/sfml/x86/lib/sfml-window-s-d.lib ../deps/sfml/x86/lib/sfml-graphics-s-d.lib ../deps/sfml/x86/lib/freetype.lib winmm.lib opengl32.lib shell32.lib gdi32.lib user32.lib advapi32.lib


IF EXIST %~dp0*.obj (DEL "%~dp0*.obj")
IF EXIST %~dp0*.ilk (DEL "%~dp0*.ilk")
IF EXIST %~dp0*.exe  (MOVE %~dp0*.exe %~dp0..\bin)