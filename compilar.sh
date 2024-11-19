#!/bin/bash
include_dir="./include"
source="./source/auxiliares.c ./source/dstring.c ./source/hospital.c ./source/main.c ./source/misc.c"
$1 -o ./hospital_app -iquote $include_dir $source