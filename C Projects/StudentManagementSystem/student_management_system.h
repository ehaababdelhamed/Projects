/******************************************************************************
 * File Name: student_mangement_system.c
 * Description: Header file for student management system
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/

#ifndef STUDENT_MANAGEMENT_SYSTEM_H_
#define STUDENT_MANAGEMENT_SYSTEM_H_

#include "Platform_Types.h"
#include "fifo.h"

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
#define MINCOURSESID Math1
#define MAXCOURSESID Robotics

typedef enum{
	SMS_PRINT_TASKS,
	SMS_ADD_STUDENT_MANUALLY,
	SMS_ADD_STUDENT_FROM_FILE,
	SMS_FIND_STUDENT_BY_ROLL,
	SMS_FIND_STUDENT_BY_NAME,
	SMS_FIND_STUDENT_BY_COURSES,
	SMS_FIND_TOTAL_STUDENTS,
	SMS_DELETE_STUDENT_BY_ROLL,
	SMS_UPDATE_STUDENT_BY_ROLL,
	SMS_SHOW_INFORMATION,
	SMS_EXIT
}SMS_states_t;

typedef enum{
	SMS_UPDATE_FIRST_NAME=1,
	SMS_UPDATE_SECOND_NAME,
	SMS_UPDATE_ROLL_NUMBER,
	SMS_UPDATE_GPA,
	SMS_UPDATE_COURSES,
	SMS_UPDATA_BACK,
	SMS_UPDATE_ADD_COURSE=1,
	SMS_UPDATE_DELETE_COURSE=2
}SMS_updata_options_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/*******************************************************************************
 * Function Name: SMS_printWelcomeMessage
 * Description: Function to print welcome message
 ******************************************************************************/
void SMS_printWelcomeMessage(void);
/*******************************************************************************
 * Function Name: SMS_printSystemTasks
 * Description: Function to print all tasks in the the system
 ******************************************************************************/
void SMS_printSystemTasks(void);

/*******************************************************************************
 * Function Name: SMS_init
 * Description: Function to initialize buffer in student management system
 ******************************************************************************/
void SMS_init(FIFO_Buf_t *fifo_buf,Student_t *buffer,uint32 size);

/*******************************************************************************
 * Function Name: SMS_AddStudentDetialManually
 * Description: Function to get the student first name ,second name
 * ,GPA and Courses id Manually form user
 ******************************************************************************/
void SMS_AddStudentDetialManually(FIFO_Buf_t *fifo_buf);

/*******************************************************************************
 * Function Name: SMS_AddStudentDetialFromFile
 * Description: Function to get the student first name ,second name
 * ,GPA and Courses id form text file
 ******************************************************************************/
void SMS_AddStudentDetialFromFile(FIFO_Buf_t *fifo_buf);

/*******************************************************************************
 * Function Name: SMS_FindStudentByRollNumber
 * Description: Function to search for the student by its roll number
 ******************************************************************************/
void SMS_FindStudentByRollNumber(FIFO_Buf_t *fifo_buf);

/*******************************************************************************
 * Function Name: SMS_FindStudentByFirstName
 * Description: Function to search for the student by its first name
 ******************************************************************************/
void SMS_FindStudentByFirstName(FIFO_Buf_t *fifo_buf);

/*******************************************************************************
 * Function Name: SMS_FindStudentByFirstName
 * Description: Function to search for the student by its first name
 ******************************************************************************/
void SMS_FindStudentsRegisteredInCourse(FIFO_Buf_t *fifo_buf);

/*******************************************************************************
 * Function Name: SMS_CountStudents
 * Description: Function to count registration students
 ******************************************************************************/
void SMS_CountStudents(FIFO_Buf_t *fifo_buf);

/*******************************************************************************
 * Function Name: SMS_DeleteStudent
 * Description: Function to delete student from the system
 ******************************************************************************/
void SMS_DeleteStudent(FIFO_Buf_t *fifo_buf);

/*******************************************************************************
 * Function Name: SMS_UpdateStudent
 * Description: Function to update the information of student
 ******************************************************************************/
void SMS_UpdateStudent(FIFO_Buf_t *fifo_buf);
/*******************************************************************************
 * Function Name: SMS_displayAllInformation
 * Description: Function to display all information in the system
 ******************************************************************************/
void SMS_displayAllInformation(FIFO_Buf_t *fifo_buf);

#endif /* STUDENT_MANAGEMENT_SYSTEM_H_ */
