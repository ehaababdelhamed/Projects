################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LDR.c \
../Main.c \
../Servo.c \
../Timer1_PWM.c \
../adc.c \
../gpio.c \
../lcd.c 

OBJS += \
./LDR.o \
./Main.o \
./Servo.o \
./Timer1_PWM.o \
./adc.o \
./gpio.o \
./lcd.o 

C_DEPS += \
./LDR.d \
./Main.d \
./Servo.d \
./Timer1_PWM.d \
./adc.d \
./gpio.d \
./lcd.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


