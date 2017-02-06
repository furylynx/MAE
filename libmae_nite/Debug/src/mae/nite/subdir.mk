################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mae/nite/device_info.cpp \
../src/mae/nite/nite_controller.cpp \
../src/mae/nite/nite_farm.cpp 

OBJS += \
./src/mae/nite/device_info.o \
./src/mae/nite/nite_controller.o \
./src/mae/nite/nite_farm.o 

CPP_DEPS += \
./src/mae/nite/device_info.d \
./src/mae/nite/nite_controller.d \
./src/mae/nite/nite_farm.d 


# Each subdirectory must supply rules for building sources it contributes
src/mae/nite/%.o: ../src/mae/nite/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include/ -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed/ -I/usr/include/c++/4.8/ -I/usr/include/ -I/usr/include/x86_64-linux-gnu/c++/4.8/bits -I/usr/local/include -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include/x86_64-linux-gnu/ -I/usr/include/ni/ -I/usr/include/nite/ -I/usr/local/java/jdk1.7.0_45/include/ -I/usr/local/java/jdk1.7.0_45/include/linux/ -I"/sda7/data/workspace-git/MAE/libmae/include" -O0 -g3 -Wall -c -fmessage-length=0 -Wno-reorder -Wno-pragmas -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


