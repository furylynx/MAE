 #!/bin/bash

swig -c++ -java -outdir release/java/ mae/mae.i

#gcc -std=c++0x -O3 -Wall -c -fmessage-length=0 -fPIC $(find ../src -name '*.cxx')
#gcc -shared $(find ../src -name '*.o') -o libmae_wrapper.so

#add other commands for other languages if required; this may require to adjust the configuration files
#e.g.: swig -c++ -csharp -outdir release/csharp/ mae/mae.i 
