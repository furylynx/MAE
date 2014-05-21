################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/model/GeneralEnrichedPose.cpp \
../src/model/GeneralJoint.cpp \
../src/model/GeneralPose.cpp \
../src/model/GeneralSkeleton.cpp 

OBJS += \
./src/model/GeneralEnrichedPose.o \
./src/model/GeneralJoint.o \
./src/model/GeneralPose.o \
./src/model/GeneralSkeleton.o 

CPP_DEPS += \
./src/model/GeneralEnrichedPose.d \
./src/model/GeneralJoint.d \
./src/model/GeneralPose.d \
./src/model/GeneralSkeleton.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/%.o: ../src/model/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/include/c++/4.8 -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include -I/usr/include/opencv2 -I/usr/include/opencv2/core -I/usr/include/x86_64-linux-gnu -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


