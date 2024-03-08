################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GL_Related.cpp \
../Simulation.cpp 

CPP_DEPS += \
./GL_Related.d \
./Simulation.d 

OBJS += \
./GL_Related.o \
./Simulation.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./GL_Related.d ./GL_Related.o ./Simulation.d ./Simulation.o

.PHONY: clean--2e-

