################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_Prog.c \
../GIE_program.c \
../KPD_Prog.c \
../LCD_Prog.c \
../TIMER_program.c \
../main.c 

OBJS += \
./DIO_Prog.o \
./GIE_program.o \
./KPD_Prog.o \
./LCD_Prog.o \
./TIMER_program.o \
./main.o 

C_DEPS += \
./DIO_Prog.d \
./GIE_program.d \
./KPD_Prog.d \
./LCD_Prog.d \
./TIMER_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


