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
../cppimpl.cpp \
../main.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
cppimpl.o \
main.o

OBJS_AS_ARGS +=  \
cppimpl.o \
main.o

C_DEPS +=  \
cppimpl.d \
main.d

C_DEPS_AS_ARGS +=  \
cppimpl.d \
main.d

OUTPUT_FILE_PATH +=coro.elf

OUTPUT_FILE_PATH_AS_ARGS +=coro.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./cppimpl.o: .././cppimpl.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 12.1.0
	$(QUOTE)D:\Soft\7.0\gcc_toolchain\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Soft\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../../../../../../../Soft/7.0/avr-libstdcpp/include" -I"../../../../../asyncruino/include"  -O0 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g3 -Wall  -mmcu=atmega328p  -c -std=c++20 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./main.o: .././main.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 12.1.0
	$(QUOTE)D:\Soft\7.0\gcc_toolchain\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Soft\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../../../../../../../Soft/7.0/avr-libstdcpp/include" -I"../../../../../asyncruino/include"  -O0 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g3 -Wall  -mmcu=atmega328p  -c -std=c++20 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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
	@echo Invoking: AVR8/GNU Linker : 12.1.0
	$(QUOTE)D:\Soft\7.0\gcc_toolchain\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="coro.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections  -mmcu=atmega328p   
	@echo Finished building target: $@
	"D:\Soft\7.0\gcc_toolchain\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "coro.elf" "coro.hex"
	"D:\Soft\7.0\gcc_toolchain\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "coro.elf" "coro.eep" || exit 0
	"D:\Soft\7.0\gcc_toolchain\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-objdump.exe" -h -S "coro.elf" > "coro.lss"
	"D:\Soft\7.0\gcc_toolchain\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "coro.elf" "coro.srec"
	"D:\Soft\7.0\gcc_toolchain\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-size.exe" "coro.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "coro.elf" "coro.a" "coro.hex" "coro.lss" "coro.eep" "coro.map" "coro.srec" "coro.usersignatures"
	