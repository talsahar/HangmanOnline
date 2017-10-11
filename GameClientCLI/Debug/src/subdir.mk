################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ClientCLI.cpp \
../src/Main.cpp 

OBJS += \
./src/ClientCLI.o \
./src/Main.o 

CPP_DEPS += \
./src/ClientCLI.d \
./src/Main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/ttt/GameClient/src" -I"/home/user/Desktop/ttt/Game/src" -I"/home/user/Desktop/ttt/Utils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


