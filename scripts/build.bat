@echo off
REM -Od = disable optimisation, -O2 = fast code
set CommonCompilerFlags=-MTd -nologo -GR- -EHsc -O2 -W4 -wd4201 -wd4100 -wd4189 -wd4324 -FC -Z7
set CommonLinkerFlags= -incremental:no -opt:ref

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

REM x64 build
set srcPath=..\source\
cl %CommonCompilerFlags% %srcPath%raytracer.cpp /link %CommonLinkerFlags%
popd