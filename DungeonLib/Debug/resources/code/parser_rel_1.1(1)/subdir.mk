################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../resources/code/parser_rel_1.1(1)/diction.cpp \
../resources/code/parser_rel_1.1(1)/lexical.cpp \
../resources/code/parser_rel_1.1(1)/parser.cpp \
../resources/code/parser_rel_1.1(1)/parser_test.cpp \
../resources/code/parser_rel_1.1(1)/parsestr.cpp \
../resources/code/parser_rel_1.1(1)/pnfa.cpp \
../resources/code/parser_rel_1.1(1)/regex.cpp \
../resources/code/parser_rel_1.1(1)/regex_test.cpp \
../resources/code/parser_rel_1.1(1)/sentence.cpp \
../resources/code/parser_rel_1.1(1)/test.cpp \
../resources/code/parser_rel_1.1(1)/vocab.cpp 

OBJS += \
./resources/code/parser_rel_1.1(1)/diction.o \
./resources/code/parser_rel_1.1(1)/lexical.o \
./resources/code/parser_rel_1.1(1)/parser.o \
./resources/code/parser_rel_1.1(1)/parser_test.o \
./resources/code/parser_rel_1.1(1)/parsestr.o \
./resources/code/parser_rel_1.1(1)/pnfa.o \
./resources/code/parser_rel_1.1(1)/regex.o \
./resources/code/parser_rel_1.1(1)/regex_test.o \
./resources/code/parser_rel_1.1(1)/sentence.o \
./resources/code/parser_rel_1.1(1)/test.o \
./resources/code/parser_rel_1.1(1)/vocab.o 

CPP_DEPS += \
./resources/code/parser_rel_1.1(1)/diction.d \
./resources/code/parser_rel_1.1(1)/lexical.d \
./resources/code/parser_rel_1.1(1)/parser.d \
./resources/code/parser_rel_1.1(1)/parser_test.d \
./resources/code/parser_rel_1.1(1)/parsestr.d \
./resources/code/parser_rel_1.1(1)/pnfa.d \
./resources/code/parser_rel_1.1(1)/regex.d \
./resources/code/parser_rel_1.1(1)/regex_test.d \
./resources/code/parser_rel_1.1(1)/sentence.d \
./resources/code/parser_rel_1.1(1)/test.d \
./resources/code/parser_rel_1.1(1)/vocab.d 


# Each subdirectory must supply rules for building sources it contributes
resources/code/parser_rel_1.1(1)/diction.o: ../resources/code/parser_rel_1.1(1)/diction.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"resources/code/parser_rel_1.1(1)/diction.d" -MT"resources/code/parser_rel_1.1(1)/diction.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

resources/code/parser_rel_1.1(1)/lexical.o: ../resources/code/parser_rel_1.1(1)/lexical.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"resources/code/parser_rel_1.1(1)/lexical.d" -MT"resources/code/parser_rel_1.1(1)/lexical.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

resources/code/parser_rel_1.1(1)/parser.o: ../resources/code/parser_rel_1.1(1)/parser.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"resources/code/parser_rel_1.1(1)/parser.d" -MT"resources/code/parser_rel_1.1(1)/parser.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

resources/code/parser_rel_1.1(1)/parser_test.o: ../resources/code/parser_rel_1.1(1)/parser_test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"resources/code/parser_rel_1.1(1)/parser_test.d" -MT"resources/code/parser_rel_1.1(1)/parser_test.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

resources/code/parser_rel_1.1(1)/parsestr.o: ../resources/code/parser_rel_1.1(1)/parsestr.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"resources/code/parser_rel_1.1(1)/parsestr.d" -MT"resources/code/parser_rel_1.1(1)/parsestr.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

resources/code/parser_rel_1.1(1)/pnfa.o: ../resources/code/parser_rel_1.1(1)/pnfa.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"resources/code/parser_rel_1.1(1)/pnfa.d" -MT"resources/code/parser_rel_1.1(1)/pnfa.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

resources/code/parser_rel_1.1(1)/regex.o: ../resources/code/parser_rel_1.1(1)/regex.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"resources/code/parser_rel_1.1(1)/regex.d" -MT"resources/code/parser_rel_1.1(1)/regex.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

resources/code/parser_rel_1.1(1)/regex_test.o: ../resources/code/parser_rel_1.1(1)/regex_test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"resources/code/parser_rel_1.1(1)/regex_test.d" -MT"resources/code/parser_rel_1.1(1)/regex_test.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

resources/code/parser_rel_1.1(1)/sentence.o: ../resources/code/parser_rel_1.1(1)/sentence.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"resources/code/parser_rel_1.1(1)/sentence.d" -MT"resources/code/parser_rel_1.1(1)/sentence.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

resources/code/parser_rel_1.1(1)/test.o: ../resources/code/parser_rel_1.1(1)/test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"resources/code/parser_rel_1.1(1)/test.d" -MT"resources/code/parser_rel_1.1(1)/test.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

resources/code/parser_rel_1.1(1)/vocab.o: ../resources/code/parser_rel_1.1(1)/vocab.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"resources/code/parser_rel_1.1(1)/vocab.d" -MT"resources/code/parser_rel_1.1(1)/vocab.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


