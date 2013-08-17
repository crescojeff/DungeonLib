################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cresco.ai.dungeonlib.data/entities/DungeonAgent.cpp 

OBJS += \
./src/cresco.ai.dungeonlib.data/entities/DungeonAgent.o 

CPP_DEPS += \
./src/cresco.ai.dungeonlib.data/entities/DungeonAgent.d 


# Each subdirectory must supply rules for building sources it contributes
src/cresco.ai.dungeonlib.data/entities/%.o: ../src/cresco.ai.dungeonlib.data/entities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


