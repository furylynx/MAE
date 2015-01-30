#! /bin/sh

if [ -d include/ ]
then
	echo "clearing include/ folder"
	rm -r include/*
else
	echo "creating include folder"
	mkdir include
fi

cd src
#find . -name '*.hpp' -exec cp -iv --parents -t ../include/ {} +
find . \( -name '*.hpp' -a \! -name 'indexer_fix.hpp' \) -exec cp -iv --parents -t ../include/ {} +
