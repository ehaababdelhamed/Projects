/*
 ================================================================================================
 Name        : HMI-ECU.c
 Author      : Ehab Mohamed Abdelhamed
 Description : HMI_ECU for door locker security system
 Date        : 10/7/2022
 ================================================================================================
 */

#include "HMI_ECU.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 g_password[MAXNUMBERS] = { 0 };
uint8 g_passwordSize = 0;
uint16 g_ticks = 0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/****************************display functions******************************************/

/*
 * Description: Function to display main options on screen
 */

void displayMainOption() {
	LCD_displayStringRowColumn(0, 0, "+: Open door");
	LCD_displayStringRowColumn(1, 0, "-: Change Pass");
}

/*
 * Description: call back Function by timer to calcuate time of door open
 * 15 seconds CW
 * 3 seconds
 * 15 seconds ACW
 */
void displayOpenDoorticks(void) {
	/*ticks to calucate time*/
	g_ticks++;
}
/*
 * Description: Function to display door is open for 33 seconds
 */
void displayOpenDoor(void) {
	while (1) {
		LCD_displayStringRowColumn(0, 0, "Door is open ");
		if (g_ticks > (TIMEOFDOOROPEN * NUMBEROFTICKSPERSECOND)) {
			g_ticks = 0;
			Timer_deInit(TIMER_0);
			LCD_clearScreen();
			break;
		}
	}
}

/*
 * Description: call back Function by timer to calcuate time of alaram
 */

void displayWarningMessageticks() {
	/*ticks to calucate time*/
	g_ticks++;
}
/*
 * Description: Function to display warning message for 1 minuts
 */
void displayWarningMessage() {
	while (1) {
		LCD_displayStringRowColumn(0, 5, "Warning!");
		if (g_ticks > (TIMEOFBUZZERON * NUMBEROFTICKSPERSECOND)) {
			g_ticks = 0;
			Timer_deInit(TIMER_0);
			LCD_clearScreen();
			break;
		}
	}
	LCD_clearScreen();
}

/************************************ Password Functions*****************************************/

/*
 * Description: Function to enter new password for system
 * enter new password
 * re enter new password
 * if match send to control ECU to save it in eeprom
 */

void enterNewPassword() {
	uint8 key = 0, count = 0, check_match = SUCCESS;
	uint8 g_rePassword[MAXNUMBERS] = { 0 };
	/*
	 * key : save value from keypad;
	 * g_passwordSize : for password array ;
	 * count : for re-password array;
	 * check_match : to check match between password and re-password
	 */
	while (1) {
		LCD_clearScreen();
		LCD_displayString("Enter new Pass:");
		LCD_moveCursor(1, 0);
		g_passwordSize = 0;
		/*first loop to enter new password */
		while (1) {
			key = KEYPAD_getPressedKey();
			/*take value from keypad , if it is number save in password
			 * password isn't more than 5 numbers
			 * if user press '=' save password and break loop;
			 * */
			if (key >= 0 && key <= 9 && g_passwordSize < MAXNUMBERS) {
				g_password[g_passwordSize] = key;
				LCD_displayCharacter('*');
				g_passwordSize++;
			} else if (key == '=') {
				_delay_ms(500);
				break;
			}
			_delay_ms(500);
		}
		LCD_clearScreen();
		LCD_displayString("Verify Password:");
		LCD_moveCursor(1, 0);
		/*second loop to Re-enter new password */
		while (1) {
			/*take value from keypad , if it is number , save in re-password
			 * password isn't more than 5 numbers
			 * if user press '=' save password and break loop;
			 * */
			key = KEYPAD_getPressedKey();
			if (key >= 0 && key <= 9 && count < MAXNUMBERS) {
				g_rePassword[count] = key;
				LCD_displayCharacter('*');
				count++;
			} else if (key == '=') {
				_delay_ms(500);
				break;
			}
			_delay_ms(500);
		}
		/*error if not match in size*/
		if (g_passwordSize != count) {
			check_match = ERROR;
		}
		/* check match between password and repassword*/
		for (count = 0; count < g_passwordSize; count++) {
			if (g_password[count] != g_rePassword[count]) {
				check_match = ERROR;
			}
		}
		/*
		 * if they match , break super loop and send new password to Control ECU to save ot in Eeprom
		 * if they not match , enter new password again
		 * count1>2 password must be more than two number*/
		if (check_match == SUCCESS && g_passwordSize > 2) {
			LCD_clearScreen();
			LCD_displayString("SUCCESS");
			_delay_ms(500);
			while (UART_recieveByte() != ECU2_READY) {
			}
			UART_sendByte(g_passwordSize);
			while (UART_recieveByte() != ECU2_READY) {
						}
			for (count = 0; count < g_passwordSize; count++) {
				UART_sendByte(g_password[count]);
			}
			break;
		} else {
			LCD_clearScreen();
			if (g_passwordSize < 2) {
				LCD_displayString("Weak Password");
			} else {
				LCD_displayString("Didn't match");
			}
			_delay_ms(500);
			/*re intialize all data to enter new password again*/
			g_passwordSize = 0;
			count = 0;
			check_match = SUCCESS;
			LCD_clearScreen();
			continue;
		}
	}
}

/*
 * Description: Function to enter password to open door or change password
 * enter password
 * send to control ECU to match it with system password
 */

void enterPassword() {
	uint8 key = 0, count = 0;
	uint8 enter_password[MAXNUMBERS] = { 0 };
	LCD_clearScreen();
	LCD_displayString("Enter Password:");
	LCD_moveCursor(1, 0);
	/*loop to enter password */
	while (1) {
		key = KEYPAD_getPressedKey();
		/*take value from keypad , if it is number save in password
		 * password isn't more than 5 numbers
		 * if user press '=' save password and break loop;
		 * */
		if (key >= 0 && key <= 9 && count < MAXNUMBERS) {
			enter_password[count] = key;
			LCD_displayCharacter('*');
			count++;
			/*break loop when enter and password should more than 2 number*/
		} else if (key == '=' && count > 2) {
			LCD_clearScreen();
			_delay_ms(500);
			break;
		}
		_delay_ms(500);
	}
	/*send password to Control ECU*/
	while (UART_recieveByte() != ECU2_READY) {
	}
	for (uint8 i = 0; i < MAXNUMBERS; i++) {
		UART_sendByte(enter_password[i]);
	}
}

/*******************************************************************************
 *                             Main Function                                   *
 *******************************************************************************/

int main() {

	/************************* Intiatilations *********************************/

	SREG |= (1 << 7); /*Enable global interrupt*/
	uint8 new_password_flag = 0; /*to check if first use for system*/
	uint8 key = 0; /*to save value from keypad*/
	uint8 check_match = SUCCESS; /*to check matching*/
	uint8 missing_count = 0; /*count number of enter wrong password*/

	/* Initialize the LCD Driver */
	LCD_init();
	/* Initialize the Timer Driver by its configrations */
	Timer_ConfigType Timer_Config = { TIMER_0, COMPARE_MATCH_MODE, 0, 250,
			F_CPU_1024 };
	/* Initialize the UART Driver by its configrations */
	UART_ConfigType UART_Config = { DATA_BIT_8, ODD_PARITY, STOP_BIT_1,
	UART_BAUDRATE };
	/*read from eeprom the size of password to know if it first time use or not*/
	UART_init(&UART_Config);

	/*recieve flag value to check if it is first time using the system */
	UART_sendByte(ECU2_READY);
	new_password_flag = UART_recieveByte();

	/***************************** Super Loop *********************************/

	while (1) {
		/*For fisrt use to the system*/
		if (new_password_flag == 1) {
			enterNewPassword();
			new_password_flag = 0;
		}
		/*display main option after every opration*/

		displayMainOption();
		key = KEYPAD_getPressedKey();
		UART_sendByte(key);

		/*check if user choose open door or change password*/
		if (key == '-' || (key == '+')) {
			do {
				/*in two case user must enter the password*/
				enterPassword();
				check_match = UART_recieveByte();
				missing_count++;
				/*if enter password three times wrong system will display warning message for 1 minute*/
				if (missing_count == 3) {
					LCD_clearScreen();
					Timer0_setCallBack(&displayWarningMessageticks);
					Timer_init(&Timer_Config);
					displayWarningMessage();
				}
			} while (check_match == ERROR && missing_count != 3);
		}
		/*if user enter wright password
		 * + : door will open
		 * - : user can change system password
		 *  */
		if (key == '-') {
			if (check_match == SUCCESS) {
				enterNewPassword();
			}

		}else if (key == '+') {
			if (check_match == SUCCESS) {
				LCD_clearScreen();
				Timer0_setCallBack(&displayOpenDoorticks);
				Timer_init(&Timer_Config);
				displayOpenDoor();
			}
		}
		/*re intialize missing counter by zero*/
		missing_count = 0;
	}
}
