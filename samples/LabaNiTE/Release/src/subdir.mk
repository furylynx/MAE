################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LabaNiTE.cpp \
../src/nite_display.cpp \
../src/nitecontroller.cpp \
../src/sdl_controller.cpp 

OBJS += \
./src/LabaNiTE.o \
./src/nite_display.o \
./src/nitecontroller.o \
./src/sdl_controller.o 

CPP_DEPS += \
./src/LabaNiTE.d \
./src/nite_display.d \
./src/nitecontroller.d \
./src/sdl_controller.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include/ -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed/ -I/usr/include/opencv2/core/ -I/usr/include/opencv2/ -I"/sda7/data/workspace-git/MAE/libmae/src" -I/usr/include/c++/4.8/ -I/usr/include/ni/ -I/usr/include/ -I/usr/include/nite/ -I/usr/include/x86_64-linux-gnu/c++/4.8/bits -I/usr/local/include -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include/x86_64-linux-gnu/ -O3 -Wall -c -fmessage-length=0 -Wno-unknown-pragmas -Wno-reorder -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


