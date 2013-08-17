################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cresco.ai.dungeonlib.data/io/ResourceWriter.cpp \
../src/cresco.ai.dungeonlib.data/io/StringTokenizer.cpp \
../src/cresco.ai.dungeonlib.data/io/Tokenizer.cpp \
../src/cresco.ai.dungeonlib.data/io/TreasureString.cpp 

OBJS += \
./src/cresco.ai.dungeonlib.data/io/ResourceWriter.o \
./src/cresco.ai.dungeonlib.data/io/StringTokenizer.o \
./src/cresco.ai.dungeonlib.data/io/Tokenizer.o \
./src/cresco.ai.dungeonlib.data/io/TreasureString.o 

CPP_DEPS += \
./src/cresco.ai.dungeonlib.data/io/ResourceWriter.d \
./src/cresco.ai.dungeonlib.data/io/StringTokenizer.d \
./src/cresco.ai.dungeonlib.data/io/Tokenizer.d \
./src/cresco.ai.dungeonlib.data/io/TreasureString.d 


# Each subdirectory must supply rules for building sources it contributes
src/cresco.ai.dungeonlib.data/io/%.o: ../src/cresco.ai.dungeonlib.data/io/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


