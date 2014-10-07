 #!/bin/bash

swig -c++ -java -outdir release/java/ mae/mae.i

#-fno-strict-aliasing for avoiding strict aliasing and supressing warnings
#-I/usr/local/java/jdk1.7.0_45/include/ -I/usr/local/java/jdk1.7.0_45/include/linux/ for jni.h and jni_md.h header files
#gcc -std=c++0x -O3 -Wall -fno-strict-aliasing -c -fmessage-length=0 -fPIC $(find ../src -name '*.cxx') -I/usr/local/java/jdk1.7.0_45/include/ -I/usr/local/java/jdk1.7.0_45/include/linux/
#gcc -shared $(find ../src -name '*.o') -o libmae_wrapper.so

#add other commands for other languages if required; this may require to adjust the configuration files
#e.g.: swig -c++ -csharp -outdir release/csharp/ mae/mae.i 
