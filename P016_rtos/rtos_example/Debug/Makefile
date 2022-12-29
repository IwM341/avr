################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o

OBJS_AS_ARGS +=  \
main.o

C_DEPS +=  \
main.d

C_DEPS_AS_ARGS +=  \
main.d

OUTPUT_FILE_PATH +=rtos_example.elf

OUTPUT_FILE_PATH_AS_ARGS +=rtos_example.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+=  \
C:/Users/artem/OneDrive/Документы/Arduino/libraries/FreeRTOS/src/Release/libFreeRTOS.a

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./main.o: .././main.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Soft\ATMEL\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Soft\ATMEL\7.0\Packs\atmel\ATmega_DFP\1.6.364\include" -I"../../../framework" -I"../../../FreeRTOS"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "D:\Soft\ATMEL\7.0\Packs\atmel\ATmega_DFP\1.6.364\gcc\dev\atmega328p" -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 5.4.0
	$(QUOTE)D:\Soft\ATMEL\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="rtos_example.map" -Wl,--start-group -Wl,-lm -Wl,-lFreeRTOS  -Wl,--end-group -Wl,-L"C:\Users\artem\OneDrive\Документы\Arduino\libraries\FreeRTOS\src" -Wl,-L"C:\Users\artem\OneDrive\Документы\Arduino\libraries\FreeRTOS\src\Release" -Wl,-L"D:\Tmp\probs\AVR\FreeRTOS\Release"  -Wl,--gc-sections -mmcu=atmega328p -B "D:\Soft\ATMEL\7.0\Packs\atmel\ATmega_DFP\1.6.364\gcc\dev\atmega328p"  
	@echo Finished building target: $@
	"D:\Soft\ATMEL\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "rtos_example.elf" "rtos_example.hex"
	"D:\Soft\ATMEL\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "rtos_example.elf" "rtos_example.eep" || exit 0
	"D:\Soft\ATMEL\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "rtos_example.elf" > "rtos_example.lss"
	"D:\Soft\ATMEL\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "rtos_example.elf" "rtos_example.srec"
	"D:\Soft\ATMEL\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "rtos_example.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "rtos_example.elf" "rtos_example.a" "rtos_example.hex" "rtos_example.lss" "rtos_example.eep" "rtos_example.map" "rtos_example.srec" "rtos_example.usersignatures"
	