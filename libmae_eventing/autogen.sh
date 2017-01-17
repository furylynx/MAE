#!/bin/bash

LIBTOOLIZE=libtoolize

if [ "$(uname)" == "Darwin" ]; then
	# Mac OS X platform
	# prepended g by brew or macports since libtool already in use
	LIBTOOLIZE=glibtoolize	
fi

$LIBTOOLIZE \
&& aclocal \
&& automake --add-missing \
&& autoconf
