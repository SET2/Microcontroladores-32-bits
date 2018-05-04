################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/Cpu.c \
../Generated_Code/LED.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/TI1.c \
../Generated_Code/TU1.c \
../Generated_Code/TimerIntLdd1.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/Cpu.o \
./Generated_Code/LED.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/TI1.o \
./Generated_Code/TU1.o \
./Generated_Code/TimerIntLdd1.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/Cpu.d \
./Generated_Code/LED.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/TI1.d \
./Generated_Code/TU1.d \
./Generated_Code/TimerIntLdd1.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/mini casa/Desktop/Eder/Pós_Sistemas_Embarcados/Processadores_Embarcados/KDS_Projects/EX04_Timer/Static_Code/PDD" -I"C:/Users/mini casa/Desktop/Eder/Pós_Sistemas_Embarcados/Processadores_Embarcados/KDS_Projects/EX04_Timer/Static_Code/IO_Map" -I"C:/Users/mini casa/Desktop/Eder/Pós_Sistemas_Embarcados/Processadores_Embarcados/KDS_Projects/EX04_Timer/Sources" -I"C:/Users/mini casa/Desktop/Eder/Pós_Sistemas_Embarcados/Processadores_Embarcados/KDS_Projects/EX04_Timer/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


