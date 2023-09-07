#Makefile prabared by Eng.Ehab Moahmed Abdelhamed
CC= arm-none-eabi
CF= -g -gdwarf-2 -mcpu=cortex-m3
INCS=-I .
SRC= $(wildcard *.c)
ASM= $(wildcard *.s)
OBJ= $(SRC:.c=.o)  $(ASM:.s=.o)
ProjectName=PressureControllerSystem

all: $(ProjectName).bin
		@echo "****** Building is done *******"

$(ProjectName).bin:$(ProjectName).elf
	$(CC)-objcopy.exe -O binary $< $@

$(ProjectName).elf:$(OBJ) linker_script.ld
	$(CC)-ld -T linker_script.ld $(LIBS) $(OBJ) -o $@ -Map=Map_file.map

%.o : %.c
	$(CC)-gcc -c $(CF) $(INCS) $< -o $@

%.o : %.s
	$(CC)-as.exe  -c $(CF) $< -o $@

clean_all:
	rm *.o *.elf *.bin
	@echo "**** Everything is clean ****"

clean:
	rm *.elf *.bin
	

	
	
	