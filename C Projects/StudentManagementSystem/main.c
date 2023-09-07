/*
 * main.c
 *
 *  Created on: ???/???/????
 *      Author: Ehab Mohamed
 */
#include "student_management_system.h"
#include <stdio.h>

/*******************************************************************************
 *                             User Configuration                              *
 *******************************************************************************/
#define MAXNUMOFSTUDENTS (50U)

FIFO_Buf_t student_fifo_buf;
Student_t studentBuffer[MAXNUMOFSTUDENTS];
SMS_states_t SMS_state_id= SMS_PRINT_TASKS;

int main(void){
	//To solve input/output buffer bug in eclipse
	setbuf(stdout,NULL);
	SMS_init(&student_fifo_buf, studentBuffer, MAXNUMOFSTUDENTS);
	SMS_printWelcomeMessage();
	while(1){
		switch(SMS_state_id){
		case SMS_PRINT_TASKS:
			SMS_printSystemTasks();
			scanf("%u",&SMS_state_id);
			break;
		case SMS_ADD_STUDENT_MANUALLY:
			SMS_AddStudentDetialManually(&student_fifo_buf);
			SMS_state_id= SMS_PRINT_TASKS;
			break;
		case SMS_ADD_STUDENT_FROM_FILE:
			SMS_AddStudentDetialFromFile(&student_fifo_buf);
			SMS_state_id= SMS_PRINT_TASKS;
			break;
		case SMS_FIND_STUDENT_BY_ROLL:
			SMS_FindStudentByRollNumber(&student_fifo_buf);
			SMS_state_id= SMS_PRINT_TASKS;
			break;
		case SMS_FIND_STUDENT_BY_NAME:
			SMS_FindStudentByFirstName(&student_fifo_buf);
			SMS_state_id= SMS_PRINT_TASKS;
			break;
		case SMS_FIND_STUDENT_BY_COURSES:
			SMS_FindStudentsRegisteredInCourse(&student_fifo_buf);
			SMS_state_id= SMS_PRINT_TASKS;
			break;
		case SMS_FIND_TOTAL_STUDENTS:
			SMS_CountStudents(&student_fifo_buf);
			SMS_state_id= SMS_PRINT_TASKS;
			break;
		case SMS_DELETE_STUDENT_BY_ROLL:
			SMS_DeleteStudent(&student_fifo_buf);
			SMS_state_id= SMS_PRINT_TASKS;
			break;
		case SMS_UPDATE_STUDENT_BY_ROLL:
			SMS_UpdateStudent(&student_fifo_buf);
			SMS_state_id= SMS_PRINT_TASKS;
			break;
		case SMS_SHOW_INFORMATION:
			SMS_displayAllInformation(&student_fifo_buf);
			SMS_state_id= SMS_PRINT_TASKS;
			break;
		case SMS_EXIT:
			SMS_state_id= SMS_EXIT;
			break;
		default:
			printf("WRONG CHOICE NUMBER!\n");
			SMS_state_id= SMS_PRINT_TASKS;
			break;
		}
		if(SMS_state_id == SMS_EXIT){
			printf("\t === Student Management SYstem Exit===\n");
			break;
		}
	}
	return 0;
}
