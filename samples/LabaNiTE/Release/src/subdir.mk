################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LabaNiTE.cpp \
../src/nite_display.cpp \
../src/nite_recognition_display.cpp \
../src/nitecontroller.cpp \
../src/sdl_controller.cpp \
../src/sequence_printer.cpp 

OBJS += \
./src/LabaNiTE.o \
./src/nite_display.o \
./src/nite_recognition_display.o \
./src/nitecontroller.o \
./src/sdl_controller.o \
./src/sequence_printer.o 

CPP_DEPS += \
./src/LabaNiTE.d \
./src/nite_display.d \
./src/nite_recognition_display.d \
./src/nitecontroller.d \
./src/sdl_controller.d \
./src/sequence_printer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include/ -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed/ -I/usr/include/opencv2/core/ -I/usr/include/opencv2/ -I/usr/include/c++/4.8/ -I/usr/include/ -I/usr/include/x86_64-linux-gnu/c++/4.8/bits -I/usr/local/include -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include/x86_64-linux-gnu/ -I/usr/include/libxml2 -I/usr/include/glibmm-2.4 -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/sigc++-2.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/libxml++-2.6 -I/usr/lib/libxml++-2.6/include -I"/sda7/data/workspace-git/MAE/libmae/src" -I/usr/include/ni/ -I/usr/include/nite/ -O3 -Wall -c -fmessage-length=0 -Wno-unknown-pragmas -Wno-reorder -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


