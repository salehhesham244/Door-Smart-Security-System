################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BUZ.c \
../DC.c \
../MC2.c \
../TIM1.c \
../external_eeprom.c \
../gpio.c \
../pwm.c \
../twi.c \
../uart.c 

OBJS += \
./BUZ.o \
./DC.o \
./MC2.o \
./TIM1.o \
./external_eeprom.o \
./gpio.o \
./pwm.o \
./twi.o \
./uart.o 

C_DEPS += \
./BUZ.d \
./DC.d \
./MC2.d \
./TIM1.d \
./external_eeprom.d \
./gpio.d \
./pwm.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


