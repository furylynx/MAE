FROM ubuntu:bionic

# configure time zone (UTC)
ENV TZ=UTC
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# install build tools and dependencies
RUN apt-get update && apt-get install -y \
  build-essential \
  openjdk-8-jdk \
  groovy \
  cmake \
  gradle \
  swig3.0 \
  libopencv-dev \
  libxml++2.6-dev \
  libboost-all-dev \
  libsdl2-dev \
  libsdl2-image-dev \
  libsdl2-ttf-dev \
  librsvg2-dev

# set environment
ENV JAVA_HOME "/usr/lib/jvm/java-8-openjdk-amd64"

# copy files/directories
RUN mkdir /MAE
ADD libmae/ /MAE/libmae
ADD libmae_demo/ /MAE/libmae_demo
ADD libmae_eventing/ /MAE/libmae_eventing
ADD libmae-java-wrapper/ /MAE/libmae-java-wrapper
ADD samples/ /MAE/samples
ADD cmake/ /MAE/cmake
ADD mae.json /MAE/

# build library
RUN cd /MAE/libmae && cmake . && make && make install
RUN cd /MAE/libmae_demo && cmake . && make && make install
RUN cd /MAE/libmae_eventing && cmake . && make && make install
RUN cd /MAE/libmae-java-wrapper && gradle install
RUN cd /MAE/samples/minimal-libmae && cmake . && make

# cleanup and install required packages
RUN apt-get purge -y \
  build-essential \
  cmake \
  swig3.0 \
  libopencv-dev \
  libxml++2.6-dev \
  libboost-all-dev \
  libsdl2-dev \
  libsdl2-image-dev \
  libsdl2-ttf-dev
RUN apt-get update && apt-get install -y \
  libopencv-core3.2 \
  libxml++2.6-2v5 \
  libboost-system1.62.0 \
  libsdl2-2.0-0 \
  libsdl2-image-2.0-0 \
  libsdl2-ttf-2.0-0
RUN apt-get -y autoremove

# define entrypoint
WORKDIR /MAE/samples/minimal-libmae
ENTRYPOINT ./minimal-libmae
