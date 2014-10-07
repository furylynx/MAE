 #!/bin/bash

swig -c++ -java -outdir release/java/ mae/mae.i 

#add other commands for other languages if required; this may require to adjust the configuration files
#e.g.: swig -c++ -csharp -outdir release/csharp/ mae/mae.i 
