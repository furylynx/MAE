#! /bin/sh


cd src
find . -name '*.hpp' -exec cp -iv --parents -t ../include/ {} +