@echo off

cl /nologo /c -I vehiclebase.h vehiclebase.cc
cl /nologo /c -I car.h car.cc
cl /nologo /c -I motorbike.h motorbike.cc
cl /nologo /c -I plane.h plane.cc
cl /nologo /c -I car.h -I motorbike.h -I vehiclebase.h main.cc

cl /nologo /Fe:main.exe *.obj
(DEL "*.obj")