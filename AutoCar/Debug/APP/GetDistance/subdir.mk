################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/GetDistance/GetDistance.c 

OBJS += \
./APP/GetDistance/GetDistance.o 

C_DEPS += \
./APP/GetDistance/GetDistance.d 


# Each subdirectory must supply rules for building sources it contributes
APP/GetDistance/%.o: ../APP/GetDistance/%.c APP/GetDistance/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


