################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fl/FLLabanSequence.cpp \
../src/fl/FLLabanSubsequence.cpp 

OBJS += \
./src/fl/FLLabanSequence.o \
./src/fl/FLLabanSubsequence.o 

CPP_DEPS += \
./src/fl/FLLabanSequence.d \
./src/fl/FLLabanSubsequence.d 


# Each subdirectory must supply rules for building sources it contributes
src/fl/%.o: ../src/fl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


