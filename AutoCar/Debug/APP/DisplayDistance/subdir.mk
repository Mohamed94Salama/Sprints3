################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/DisplayDistance/DisplayDistance.c 

OBJS += \
./APP/DisplayDistance/DisplayDistance.o 

C_DEPS += \
./APP/DisplayDistance/DisplayDistance.d 


# Each subdirectory must supply rules for building sources it contributes
APP/DisplayDistance/%.o: ../APP/DisplayDistance/%.c APP/DisplayDistance/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


