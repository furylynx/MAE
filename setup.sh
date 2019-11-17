# REQUIREMENTS
sudo apt install build-essential git openjdk-8-jdk groovy gradle maven cmake

echo 'export JAVA_HOME="/usr/lib/jvm/java-8-openjdk-amd64"' >> ~/.profile
source ~/.profile

sudo apt install swig3.0

sudo apt install libopencv-dev libxml++2.6-dev libboost-all-dev libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev

# CORE LIBS
cd libmae/
cmake .
make
sudo make install

cd ../libmae-java-wrapper/
gradle install

cd ../libmae_demo/
cmake .
make
sudo make install

cd ../libmae_eventing/
cmake .
make
sudo make install

# SAMPLES
cd ../samples/minimal-libmae/
cmake .
make
./minimal-libmae

cd ../minimal-libmae-java/
gradle run

cd ../laban-sequence-converter/
cmake .
make
./laban-sequence-converter
