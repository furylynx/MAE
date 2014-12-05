################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mae/bone.cpp \
../src/mae/dummy_pose_listener.cpp \
../src/mae/e_bone.cpp \
../src/mae/e_joint.cpp \
../src/mae/general_enriched_pose.cpp \
../src/mae/general_joint.cpp \
../src/mae/general_pose.cpp \
../src/mae/general_skeleton.cpp \
../src/mae/hierarchy.cpp \
../src/mae/hierarchy_element.cpp \
../src/mae/ini_reader.cpp \
../src/mae/kp_detector.cpp \
../src/mae/mbool.cpp \
../src/mae/mos.cpp \
../src/mae/mstr.cpp \
../src/mae/mxml.cpp 

OBJS += \
./src/mae/bone.o \
./src/mae/dummy_pose_listener.o \
./src/mae/e_bone.o \
./src/mae/e_joint.o \
./src/mae/general_enriched_pose.o \
./src/mae/general_joint.o \
./src/mae/general_pose.o \
./src/mae/general_skeleton.o \
./src/mae/hierarchy.o \
./src/mae/hierarchy_element.o \
./src/mae/ini_reader.o \
./src/mae/kp_detector.o \
./src/mae/mbool.o \
./src/mae/mos.o \
./src/mae/mstr.o \
./src/mae/mxml.o 

CPP_DEPS += \
./src/mae/bone.d \
./src/mae/dummy_pose_listener.d \
./src/mae/e_bone.d \
./src/mae/e_joint.d \
./src/mae/general_enriched_pose.d \
./src/mae/general_joint.d \
./src/mae/general_pose.d \
./src/mae/general_skeleton.d \
./src/mae/hierarchy.d \
./src/mae/hierarchy_element.d \
./src/mae/ini_reader.d \
./src/mae/kp_detector.d \
./src/mae/mbool.d \
./src/mae/mos.d \
./src/mae/mstr.d \
./src/mae/mxml.d 


# Each subdirectory must supply rules for building sources it contributes
src/mae/%.o: ../src/mae/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include/ -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed/ -I/usr/include/opencv2/core/ -I/usr/include/opencv2/ -I/usr/include/c++/4.8/ -I/usr/include/ -I/usr/include/x86_64-linux-gnu/c++/4.8/bits -I/usr/local/include -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include/x86_64-linux-gnu/ -I/usr/include/libxml2 -I/usr/include/glibmm-2.4 -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/sigc++-2.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/libxml++-2.6 -I/usr/lib/libxml++-2.6/include -I/usr/local/java/jdk1.7.0_45/include/ -I/usr/local/java/jdk1.7.0_45/include/linux/ -O3 -Wall -c -fmessage-length=0 -fno-strict-aliasing -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


