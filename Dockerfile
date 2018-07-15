FROM ubuntu:bionic
#RUN ln -fs /usr/share/zoneinfo/UTC /etc/localtime && dpkg-reconfigure -f noninteractive tzdata
ENV TZ=UTC
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
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
  libsdl2-ttf-dev #\
#  git
ENV JAVA_HOME "/usr/lib/jvm/java-8-openjdk-amd64"
RUN mkdir /MAE
ADD libmae/ /MAE/libmae
ADD libmae_demo/ /MAE/libmae_demo
ADD libmae_eventing/ /MAE/libmae_eventing
ADD libmae-java-wrapper/ /MAE/libmae-java-wrapper
ADD samples/ /MAE/samples
ADD cmake/ /MAE/cmake
ADD mae.json /MAE/
#RUN git clone -b master --single-branch https://github.com/furylynx/MAE.git /MAE
RUN cd /MAE/libmae && cmake . && make && make install
RUN cd /MAE/libmae_demo && cmake . && make && make install
RUN cd /MAE/libmae_eventing && cmake . && make && make install
RUN cd /MAE/libmae-java-wrapper && gradle install
RUN cd /MAE/samples/minimal-libmae && cmake . && make
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

ENTRYPOINT /MAE/samples/minimal-libmae/minimal-libmae
