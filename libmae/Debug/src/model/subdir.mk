################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/model/GeneralEnrichedPose.cpp \
../src/model/GeneralPose.cpp \
../src/model/GeneralSkeleton.cpp 

OBJS += \
./src/model/GeneralEnrichedPose.o \
./src/model/GeneralPose.o \
./src/model/GeneralSkeleton.o 

CPP_DEPS += \
./src/model/GeneralEnrichedPose.d \
./src/model/GeneralPose.d \
./src/model/GeneralSkeleton.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/%.o: ../src/model/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


