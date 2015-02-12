################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tutorial-nite.cpp 

OBJS += \
./src/tutorial-nite.o 

CPP_DEPS += \
./src/tutorial-nite.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include/ -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed/ -I/usr/include/c++/4.8/ -I/usr/include/ -I/usr/include/x86_64-linux-gnu/c++/4.8/bits -I/usr/local/include -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include/x86_64-linux-gnu/ -I/usr/include/nite/ -I/usr/include/ni/ -I"/sda7/data/workspace-git/MAE/libmae/include" -I"/sda7/data/workspace-git/MAE/libmae_nite/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


