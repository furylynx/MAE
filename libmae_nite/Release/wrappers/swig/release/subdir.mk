################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CXX_SRCS += \
../wrappers/swig/release/maenite_wrap_java.cxx 

OBJS += \
./wrappers/swig/release/maenite_wrap_java.o 

CXX_DEPS += \
./wrappers/swig/release/maenite_wrap_java.d 


# Each subdirectory must supply rules for building sources it contributes
wrappers/swig/release/%.o: ../wrappers/swig/release/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include/ -I/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed/ -I/usr/include/opencv2/core/ -I/usr/include/c++/4.8/ -I/usr/include/ -I/usr/local/include -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include/x86_64-linux-gnu/ -I/usr/include/ni/ -I/usr/include/nite/ -I/usr/local/java/jdk1.7.0_45/include/ -I/usr/local/java/jdk1.7.0_45/include/linux/ -I"/sda7/data/workspace-git/MAE/libmae/include" -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


