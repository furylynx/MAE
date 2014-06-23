################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fl/bvh_controller.cpp \
../src/fl/bvh_spec.cpp \
../src/fl/fl_joint.cpp \
../src/fl/fl_movement_controller.cpp \
../src/fl/fl_pose_detector.cpp \
../src/fl/fl_skeleton.cpp \
../src/fl/fl_skeleton_controller.cpp \
../src/fl/laban_sequence.cpp \
../src/fl/laban_sequence_generator.cpp \
../src/fl/laban_subsequence.cpp \
../src/fl/math.cpp 

OBJS += \
./src/fl/bvh_controller.o \
./src/fl/bvh_spec.o \
./src/fl/fl_joint.o \
./src/fl/fl_movement_controller.o \
./src/fl/fl_pose_detector.o \
./src/fl/fl_skeleton.o \
./src/fl/fl_skeleton_controller.o \
./src/fl/laban_sequence.o \
./src/fl/laban_sequence_generator.o \
./src/fl/laban_subsequence.o \
./src/fl/math.o 

CPP_DEPS += \
./src/fl/bvh_controller.d \
./src/fl/bvh_spec.d \
./src/fl/fl_joint.d \
./src/fl/fl_movement_controller.d \
./src/fl/fl_pose_detector.d \
./src/fl/fl_skeleton.d \
./src/fl/fl_skeleton_controller.d \
./src/fl/laban_sequence.d \
./src/fl/laban_sequence_generator.d \
./src/fl/laban_subsequence.d \
./src/fl/math.d 


# Each subdirectory must supply rules for building sources it contributes
src/fl/%.o: ../src/fl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D"size_type=long unsigned int" -I/usr/include/c++/4.8 -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include -I/usr/include/opencv2 -I/usr/include/opencv2/core -I/usr/include/x86_64-linux-gnu -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


