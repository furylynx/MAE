################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/controller/kp_detector.cpp \
../src/controller/mstr.cpp 

OBJS += \
./src/controller/kp_detector.o \
./src/controller/mstr.o 

CPP_DEPS += \
./src/controller/kp_detector.d \
./src/controller/mstr.d 


# Each subdirectory must supply rules for building sources it contributes
src/controller/%.o: ../src/controller/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D"size_type=long unsigned int" -I/usr/include/c++/4.8 -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include -I/usr/include/opencv2 -I/usr/include/opencv2/core -I/usr/include/x86_64-linux-gnu -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


