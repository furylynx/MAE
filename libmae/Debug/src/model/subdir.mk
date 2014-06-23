################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/model/bone.cpp \
../src/model/general_enriched_pose.cpp \
../src/model/general_joint.cpp \
../src/model/general_pose.cpp \
../src/model/general_skeleton.cpp \
../src/model/hierarchy.cpp \
../src/model/hierarchy_element.cpp 

OBJS += \
./src/model/bone.o \
./src/model/general_enriched_pose.o \
./src/model/general_joint.o \
./src/model/general_pose.o \
./src/model/general_skeleton.o \
./src/model/hierarchy.o \
./src/model/hierarchy_element.o 

CPP_DEPS += \
./src/model/bone.d \
./src/model/general_enriched_pose.d \
./src/model/general_joint.d \
./src/model/general_pose.d \
./src/model/general_skeleton.d \
./src/model/hierarchy.d \
./src/model/hierarchy_element.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/%.o: ../src/model/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D"size_type=long unsigned int" -I/usr/include/c++/4.8 -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include -I/usr/include/opencv2 -I/usr/include/opencv2/core -I/usr/include/x86_64-linux-gnu -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


