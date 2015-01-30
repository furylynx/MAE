#! /bin/sh

#TODO check whether scripts were successful

# build swig wrappers
cd wrappers/swig/
sh swig_java_wrapper.sh


# copy header to include folder
cd ../../
sh copy_header.sh

#TODO build doxygen comments

# everything is done
echo "Ready for build now!"
