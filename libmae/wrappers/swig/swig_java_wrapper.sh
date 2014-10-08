  #!/bin/bash

#file info (modify if required)
INCONFIG="mae/mae.i"
OUTDIRJAVA="release/java/"
OUTDIRCXX="release/"
OUTFILECXX="mae_wrap"
PACKAGE=maejava
#OUTDIRCSHARP=release/csharp/

#script (modify if other language is required)
OUTPATHJAVACXX=$OUTDIRCXX$OUTFILECXX"_java.cxx"

#clear dirs
if [ -n "$OUTDIRJAVA" ];
then
	find $OUTDIRJAVA -maxdepth 1 -type f -delete	
fi

if [ -n "$OUTDIRCXX" ];
then
	find $OUTDIRCXX -maxdepth 1 -type f -delete
	#rm $(find $OUTDIRCXX -maxdepth 1 -type f)
fi

#generate java wrapper files
swig -c++ -java -package $PACKAGE -outdir $OUTDIRJAVA -o $OUTPATHJAVACXX $INCONFIG


## -- Add other commands for other languages if required; this may require to adjust the configuration files (*.i) --
## e.g.:
#
#OUTPATHCSHARPCXX=$OUTDIRCXX$OUTFILECXX"_csharp.cxx"
#
#if [ $OUTDIR != "" ];
#then
#	rm $OUTDIRCSHARP*	
#fi
#
#swig -c++ -csharp -outdir $OUTDIRCSHARP -o $OUTPATHCSHARPCXX $INCONFIG


## -- GCC compiler if required to compile independently from the libmae library --
## It is recommended to include the swig *.cxx file(s) to libmae in order to have only one library and no additional wrapper library
##
## GCC params:
## -fno-strict-aliasing for avoiding strict aliasing and supressing warnings
## -I/usr/local/java/jdk1.7.0_45/include/ -I/usr/local/java/jdk1.7.0_45/include/linux/ for jni.h and jni_md.h header files (should be adjusted to the actual path on your system)
#gcc -std=c++0x -O3 -Wall -fno-strict-aliasing -c -fmessage-length=0 -fPIC $(find $OUTDIRCXX -name '*.cxx') -I/usr/local/java/jdk1.7.0_45/include/ -I/usr/local/java/jdk1.7.0_45/include/linux/
#gcc -shared $(find $OUTDIRCXX -name '*.o') -o libmae_wrapper.so
