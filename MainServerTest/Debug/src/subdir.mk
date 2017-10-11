################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Main.cpp \
../src/MainServerTest.cpp 

OBJS += \
./src/Main.o \
./src/MainServerTest.o 

CPP_DEPS += \
./src/Main.d \
./src/MainServerTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/ttt/AuthenticationAPI/src" -I"/home/user/Desktop/ttt/MainServer/src" -I"/home/user/Desktop/ttt/Utils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


