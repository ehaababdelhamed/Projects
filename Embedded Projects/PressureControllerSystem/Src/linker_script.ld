/******************************************************************************
 * File Name: linker_scriot.ld
 * Description: linker script file for STM32F103C8T6 (32-bit Cortex-M3 CPU) 
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/
 
  
 ENTRY(_reset)
 
 MEMORY
 {
	flash (RX) : ORIGIN = 0x08000000 , LENGTH = 64K
	sram  (RWX): ORIGIN = 0x20000000 , LENGTH = 20K
 }
 
 SECTIONS
 {
	.text :
	{
			startup.o(.vectors)
			*(.text*)
			*(.rodata*)
			. = ALIGN(4) ;
			_TEXT_END = . ;
	}> flash
	
	.data :
	{	
		_DATA_START = . ;
		*(.data*)
		. = ALIGN(4) ;
		_DATA_END = . ;
	}> sram AT> flash
	
	.bss :
	{	
		_BSS_START = . ;
		*(.bss*)
		. = ALIGN(4) ;
		_BSS_END = . ;
		. = . + 0x2048 ;
		_STACK_POINTER_TOP = . ;
	}> sram
	
	/*Section for store measured pressure values*/
	.pressureRecords :
	{
		*(.pressureRecords);
	}> flash
 }