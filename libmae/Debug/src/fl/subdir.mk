################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fl/FLJoint.cpp \
../src/fl/FLLabanSequence.cpp \
../src/fl/FLLabanSequenceGenerator.cpp \
../src/fl/FLLabanSubsequence.cpp \
../src/fl/FLSkeleton.cpp \
../src/fl/FLSkeletonController.cpp 

OBJS += \
./src/fl/FLJoint.o \
./src/fl/FLLabanSequence.o \
./src/fl/FLLabanSequenceGenerator.o \
./src/fl/FLLabanSubsequence.o \
./src/fl/FLSkeleton.o \
./src/fl/FLSkeletonController.o 

CPP_DEPS += \
./src/fl/FLJoint.d \
./src/fl/FLLabanSequence.d \
./src/fl/FLLabanSequenceGenerator.d \
./src/fl/FLLabanSubsequence.d \
./src/fl/FLSkeleton.d \
./src/fl/FLSkeletonController.d 


# Each subdirectory must supply rules for building sources it contributes
src/fl/%.o: ../src/fl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/include/c++/4.8 -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include -I/usr/include/opencv2 -I/usr/include/opencv2/core -I/usr/include/x86_64-linux-gnu -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


