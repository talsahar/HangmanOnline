################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Dispatcher.cpp \
../src/IdentifiedTCP.cpp \
../src/MainServer.cpp \
../src/ProxyServer.cpp \
../src/UserLogin.cpp 

OBJS += \
./src/Dispatcher.o \
./src/IdentifiedTCP.o \
./src/MainServer.o \
./src/ProxyServer.o \
./src/UserLogin.o 

CPP_DEPS += \
./src/Dispatcher.d \
./src/IdentifiedTCP.d \
./src/MainServer.d \
./src/ProxyServer.d \
./src/UserLogin.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/ttt/AuthenticationAPI/src" -I"/home/user/Desktop/ttt/Utils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


