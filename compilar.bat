@SETLOCAL
@echo off

set include_dir=.\include
set source=.\source\auxiliares.c .\source\dstring.c .\source\hospital.c .\source\main.c .\source\misc.c

%1 -o hospital -iquote %include_dir% %source%

ENDLOCAL