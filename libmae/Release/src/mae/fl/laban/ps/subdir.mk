################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mae/fl/laban/ps/area_part.cpp \
../src/mae/fl/laban/ps/body_part.cpp \
../src/mae/fl/laban/ps/custom_limb.cpp \
../src/mae/fl/laban/ps/default_limb.cpp \
../src/mae/fl/laban/ps/digit_part.cpp \
../src/mae/fl/laban/ps/e_area.cpp \
../src/mae/fl/laban/ps/e_digit.cpp \
../src/mae/fl/laban/ps/e_joint.cpp \
../src/mae/fl/laban/ps/e_limb.cpp \
../src/mae/fl/laban/ps/e_limb_side.cpp \
../src/mae/fl/laban/ps/e_side.cpp \
../src/mae/fl/laban/ps/joint_part.cpp \
../src/mae/fl/laban/ps/prop.cpp \
../src/mae/fl/laban/ps/surface_part.cpp 

OBJS += \
./src/mae/fl/laban/ps/area_part.o \
./src/mae/fl/laban/ps/body_part.o \
./src/mae/fl/laban/ps/custom_limb.o \
./src/mae/fl/laban/ps/default_limb.o \
./src/mae/fl/laban/ps/digit_part.o \
./src/mae/fl/laban/ps/e_area.o \
./src/mae/fl/laban/ps/e_digit.o \
./src/mae/fl/laban/ps/e_joint.o \
./src/mae/fl/laban/ps/e_limb.o \
./src/mae/fl/laban/ps/e_limb_side.o \
./src/mae/fl/laban/ps/e_side.o \
./src/mae/fl/laban/ps/joint_part.o \
./src/mae/fl/laban/ps/prop.o \
./src/mae/fl/laban/ps/surface_part.o 

CPP_DEPS += \
./src/mae/fl/laban/ps/area_part.d \
./src/mae/fl/laban/ps/body_part.d \
./src/mae/fl/laban/ps/custom_limb.d \
./src/mae/fl/laban/ps/default_limb.d \
./src/mae/fl/laban/ps/digit_part.d \
./src/mae/fl/laban/ps/e_area.d \
./src/mae/fl/laban/ps/e_digit.d \
./src/mae/fl/laban/ps/e_joint.d \
./src/mae/fl/laban/ps/e_limb.d \
./src/mae/fl/laban/ps/e_limb_side.d \
./src/mae/fl/laban/ps/e_side.d \
./src/mae/fl/laban/ps/joint_part.d \
./src/mae/fl/laban/ps/prop.d \
./src/mae/fl/laban/ps/surface_part.d 


# Each subdirectory must supply rules for building sources it contributes
src/mae/fl/laban/ps/%.o: ../src/mae/fl/laban/ps/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include/ -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed/ -I/usr/include/opencv2/core/ -I/usr/include/opencv2/ -I/usr/include/c++/4.8/ -I/usr/include/ -I/usr/include/x86_64-linux-gnu/c++/4.8/bits -I/usr/local/include -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include/x86_64-linux-gnu/ -I/usr/include/libxml2 -I/usr/include/glibmm-2.4 -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/sigc++-2.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/libxml++-2.6 -I/usr/lib/libxml++-2.6/include -I/usr/local/java/jdk1.7.0_45/include/ -I/usr/local/java/jdk1.7.0_45/include/linux/ -O3 -Wall -c -fmessage-length=0 -fno-strict-aliasing -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


