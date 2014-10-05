#!/bin/bash

rm result/all/*
rm result/*

cccc --outdir=result/all $(find ../src \( -name '*.cpp' -or -name '*.hpp' -or -name '*.h' -or -name '*.c' \) )

cp result/all/cccc* result/
cp result/cccc.html result/--metrics--.html

#$(find ../src ! -name 'e_*' -and ! -name 'i_*' -and \( -name '*.cpp' -or -name '*.hpp' -or -name '*.h' -or -name '*.c' \) )
