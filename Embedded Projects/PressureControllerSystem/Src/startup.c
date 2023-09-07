/******************************************************************************
 * File Name: startup.c
 * Description: startup file for STM32F103C8T6 (32-bit Cortex-M3 CPU) 
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/

/* Enable Exceptions ... This Macro enable IRQ interrupts, by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm("CPSIE I")

/* Disable Exceptions ... This Macro disable IRQ interrupts,by clearing the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm("CPSID I")


extern unsigned long _TEXT_END;
extern unsigned long _DATA_START;
extern unsigned long _DATA_END;
extern unsigned long _BSS_START;
extern unsigned long _BSS_END;
extern unsigned long _STACK_POINTER_TOP;

 void main(void);
 void Defualt_handler(void);
  
 /*Create interrupt vector table*/
 void _reset(void);             												 	//2-Reset_handler
 void NMI_handler(void)__attribute__((weak, alias ("Defualt_handler")));         	//3-NMI_handler
 void HardFault_handler(void)__attribute__((weak, alias ("Defualt_handler")));   	//4-HardFault_handler
 void MemManage_handler(void)__attribute__((weak, alias ("Defualt_handler")));   	//5-MemManage_handlr
 void BusFault_handler(void)__attribute__((weak, alias ("Defualt_handler")));    	//6-BusFault_handler
 /*Reserved*/ 																		//7-Reserved
 void SVCall_handler(void)__attribute__((weak, alias("Defualt_handler")));       	//8-SVCall_handler
 void DebugMointor_handler(void)__attribute__((weak, alias ("Defualt_handler")));	//9-DebugMointor_handler
 /*Reserved*/ 																		//10-Reserved
 void PendSV_handler(void)__attribute__((weak, alias ("Defualt_handler")));      	//11-PendSV_handlr
 void SysTick_handler(void)__attribute__((weak, alias ("Defualt_handler")));     	//12-SysTick_handler
 void WWDG_handler(void)__attribute__((weak, alias ("Defualt_handler")));        	//13-WWDG_handlr
 void PVD_handler(void)__attribute__((weak, alias ("Defualt_handler")));         	//14-PVD_handler
 void TAMPER_handler(void)__attribute__((weak, alias ("Defualt_handler")));       	//15-TAMPER_handler
 void FLASH_handler(void)__attribute__((weak, alias ("Defualt_handler")));       	//16-FLASH_handler
 void RCC_handler(void)__attribute__((weak, alias ("Defualt_handler")));         	//17-RCC_handler
 void ECTI0_handler(void)__attribute__((weak, alias ("Defualt_handler")));       	//18-ECTI0_handler
 void ECTI1_handler(void)__attribute__((weak, alias ("Defualt_handler")));       	//19-ECTI1_handler
 void ECTI2_handler(void)__attribute__((weak, alias ("Defualt_handler")));       	//20-ECTI2_handler
 //IRQ21 .........
 //IRQ22 .........
 
 const unsigned long vectors[] __attribute__((section(".vectors")))=
 {
	(unsigned long)&_STACK_POINTER_TOP,
	(unsigned long)&_reset,
	(unsigned long)&NMI_handler,
	(unsigned long)&HardFault_handler,
	(unsigned long)&MemManage_handler,
	(unsigned long)&BusFault_handler,
	(unsigned long)0,
	(unsigned long)&SVCall_handler,
	(unsigned long)&DebugMointor_handler,
	(unsigned long)0,
	(unsigned long)&PendSV_handler,
	(unsigned long)&SysTick_handler,
	(unsigned long)&WWDG_handler,
	(unsigned long)&PVD_handler,
	(unsigned long)&TAMPER_handler,
	(unsigned long)&FLASH_handler,
	(unsigned long)&RCC_handler,
	(unsigned long)&ECTI0_handler,
	(unsigned long)&ECTI1_handler,
	(unsigned long)&ECTI2_handler
	//(unsigned long)&IRQ_21 .........
	//(unsigned long)&IRQ_22 .........
 };
 
 //Defination of reset handler
 void _reset(void){
	 //Disable all interrupt
	 Disable_Exceptions();
	 unsigned long i;
	 const unsigned char *_Ptr_Source=(unsigned char *)&_TEXT_END;
	 unsigned char  *_Ptr_Destination=(unsigned char *)&_DATA_START;
	 unsigned long _SIZE_=((unsigned long)&_DATA_END - (unsigned long)&_DATA_START);
	 //copy .data section that contian intialized data from flash to sram 
	 for(i=0;i<_SIZE_;i++){
		*(_Ptr_Destination)=*(_Ptr_Source);
		(unsigned char *)_Ptr_Destination++;
		(const unsigned char *)_Ptr_Source++;
	 }
	 //reserve .bss section in sram and intialize it by zero 
	_Ptr_Destination=(unsigned char *)&_BSS_START;
	 _SIZE_=((unsigned long)&_BSS_END - (unsigned long)&_BSS_START);
	 for(i=0;i<_SIZE_;i++){
		 *(_Ptr_Destination)=0;
		 (unsigned char *)_Ptr_Destination++;
	 }
	 //Enble all interrupt
	 Enable_Exceptions();
	 //Jump to main function
	 main();
	 while(1){}
 }
 
 void Defualt_handler(void){
	 while(1){}
 }