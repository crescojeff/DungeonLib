################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cresco.ai.dungeonlib.data/env/Dungeon.cpp \
../src/cresco.ai.dungeonlib.data/env/DungeonConfiguration.cpp \
../src/cresco.ai.dungeonlib.data/env/DungeonNode.cpp \
../src/cresco.ai.dungeonlib.data/env/DungeonObject.cpp \
../src/cresco.ai.dungeonlib.data/env/DungeonRoom.cpp 

OBJS += \
./src/cresco.ai.dungeonlib.data/env/Dungeon.o \
./src/cresco.ai.dungeonlib.data/env/DungeonConfiguration.o \
./src/cresco.ai.dungeonlib.data/env/DungeonNode.o \
./src/cresco.ai.dungeonlib.data/env/DungeonObject.o \
./src/cresco.ai.dungeonlib.data/env/DungeonRoom.o 

CPP_DEPS += \
./src/cresco.ai.dungeonlib.data/env/Dungeon.d \
./src/cresco.ai.dungeonlib.data/env/DungeonConfiguration.d \
./src/cresco.ai.dungeonlib.data/env/DungeonNode.d \
./src/cresco.ai.dungeonlib.data/env/DungeonObject.d \
./src/cresco.ai.dungeonlib.data/env/DungeonRoom.d 


# Each subdirectory must supply rules for building sources it contributes
src/cresco.ai.dungeonlib.data/env/%.o: ../src/cresco.ai.dungeonlib.data/env/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


