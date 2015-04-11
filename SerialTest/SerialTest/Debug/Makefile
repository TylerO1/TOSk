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

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Utility \
../Scripts


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../ArduinoInterface.cpp \
../ATmega328P.cpp \
../Button.cpp \
../TylerSerialIO.cpp \
../RotaryEncoder.cpp \
../SerialTest.cpp \
../Utility/BuildDate.cpp \
../Utility/BuildInfo.cpp \
../Utility/BuildNumber.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
ArduinoInterface.o \
ATmega328P.o \
Button.o \
TylerSerialIO.o \
RotaryEncoder.o \
SerialTest.o \
Utility/BuildDate.o \
Utility/BuildInfo.o \
Utility/BuildNumber.o

OBJS_AS_ARGS +=  \
ArduinoInterface.o \
ATmega328P.o \
Button.o \
TylerSerialIO.o \
RotaryEncoder.o \
SerialTest.o \
Utility/BuildDate.o \
Utility/BuildInfo.o \
Utility/BuildNumber.o

C_DEPS +=  \
ArduinoInterface.d \
ATmega328P.d \
Button.d \
TylerSerialIO.d \
RotaryEncoder.d \
SerialTest.d \
Utility/BuildDate.d \
Utility/BuildInfo.d \
Utility/BuildNumber.d

C_DEPS_AS_ARGS +=  \
ArduinoInterface.d \
ATmega328P.d \
Button.d \
TylerSerialIO.d \
RotaryEncoder.d \
SerialTest.d \
Utility/BuildDate.d \
Utility/BuildInfo.d \
Utility/BuildNumber.d

OUTPUT_FILE_PATH +=SerialTest.elf

OUTPUT_FILE_PATH_AS_ARGS +=SerialTest.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler



















./%.o: .././%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 3.4.2
	$(QUOTE)D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=16000000 -DARDUINO=104 -DARDUINO_UNO=1  -I"%ATE_HOME%\Boards\Uno\Headers"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -mmcu=atmega328p -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
	@echo Finished building: $<
	

Utility/%.o: ../Utility/%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 3.4.2
	$(QUOTE)D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=16000000 -DARDUINO=104 -DARDUINO_UNO=1  -I"%ATE_HOME%\Boards\Uno\Headers"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -mmcu=atmega328p -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
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

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 3.4.2
	$(QUOTE)D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="SerialTest.map" -Wl,--start-group -Wl,-lm -Wl,-lArduinoCore  -Wl,--end-group -Wl,-L"%ATE_HOME%\Boards\Uno\Libs\16"  -Wl,--gc-sections -mrelax -mmcu=atmega328p 
	@echo Finished building target: $@
	"D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "SerialTest.elf" "SerialTest.hex"
	"D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "SerialTest.elf" "SerialTest.eep" || exit 0
	"D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "SerialTest.elf" > "SerialTest.lss"
	"D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "SerialTest.elf" "SerialTest.srec"
	"D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-size.exe" "SerialTest.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "SerialTest.elf" "SerialTest.a" "SerialTest.hex" "SerialTest.lss" "SerialTest.eep" "SerialTest.map" "SerialTest.srec"
	