/******************************************************************************
 * File Name: student_mangement_system.c
 * Description: Source file for student management system
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/
#include "student_management_system.h"
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 *                     Private Function Prototypes                                    *
 *******************************************************************************/
static void printStudentInfo(const Student_t *st);
static void PrintCousresMap();
static void printCourseName(uint32 id);
static void UpdataCourses(Student_t *student);

/*******************************************************************************
 *                     Function Definition                                     *
 *******************************************************************************/

/*******************************************************************************
 * Function Name: SMS_printWelcomeMessage
 * Description: Function to print welcome message
 ******************************************************************************/
void SMS_printWelcomeMessage(void){
	printf("*****************************************************\n");
	printf("\tWelcome Student Management System\n");
	printf("*****************************************************\n");
}

/*******************************************************************************
 * Function Name: SMS_printSystemTasks
 * Description: Function to print all tasks in the the system
 ******************************************************************************/
void SMS_printSystemTasks(void){
	printf("Choose the task that you want to perform\n");
	printf("1. Add Student Details Manually \n");
	printf("2. Add Student Details From Text \n");
	printf("3. Find Student Details by Roll Number \n");
	printf("4. Find Student Details by First Name \n");
	printf("5. Find Student Details by Course ID \n");
	printf("6. Find The Total Number of Students \n");
	printf("7. Delete Student Details by Roll Number \n");
	printf("8. Update Student Details by Roll Number \n");
	printf("9. Show All Information \n");
	printf("10.Exit \n");
	printf("Enter Your Choice : ");
}

/*******************************************************************************
 * Function Name: SMS_init
 * Description: Function to initialize buffer in student management system
 ******************************************************************************/
void SMS_init(FIFO_Buf_t *fifo_buf,Student_t *buffer,uint32 size){
	FIFO_Status status;
	status=FIFO_init(fifo_buf, buffer, size);
	if(status==FIFO_NULL){
		printf("[ERROR] Student buffer is not initialized \n");
	}
}

/************************************************************************************
 * Function Name: SMS_AddStudentDetialManually
 * Description: Function to get the student first name ,second name
 * ,GPA and Courses id Manually form user
 ************************************************************************************/
void SMS_AddStudentDetialManually(FIFO_Buf_t *fifo_buf){
	Student_t *pTemp; 					//variable to loop in buffer
	uint32 rollError=0;					//to check if roll number is taken
	Student_t student;					//to save student information
	uint32 count=0;						//counter will use in for loop
	printf("------------ SMS_AddStudentDetialManually -----------\n");
	//check if FIFO is not initialized or full
	if(fifo_buf==NULL){
		printf("[ERROR] Student buffer is not initialized \n");
		return;
	}
	//check if FIFO is not initialized or full
	if(FIFO_is_full(fifo_buf)==FIFO_FULL){
		printf("[ERROR] Student buffer is full you can't add more student \n");
		return;
	}
	pTemp=fifo_buf->tail;
	//Enter student information
	printf("Enter First Name: ");
	scanf("%s",student.firstName);
	printf("Enter Second Name: ");
	scanf("%s",student.secondName);
	printf("Enter Roll Number: ");
	scanf("%lu",&student.rollNum);
	while(pTemp!=fifo_buf->head){  			//Check if roll number is taken
		if(student.rollNum==pTemp->rollNum){
			rollError=student.rollNum;
			break;
		}
		pTemp++;
	}
	printf("Enter GPA: ");
	scanf("%f",&student.GPA);
	printf("Enter Number of Courses: ");
	scanf("%lu",&student.NumOfCousres);
	PrintCousresMap();
	while(count<student.NumOfCousres){
		printf("Enter Course %lu ID : ",count+1);
		scanf("%u",&(student.CourseID[count]));
		if(student.CourseID[count]>MAXCOURSESID||student.CourseID[count]<MINCOURSESID){
			printf("ERROR COURSE ID!\n");
			continue;
		}
		count++;
	}
	//if roll number is taken display error message
	if(rollError!=0){
		printf("[ERROR] roll number %lu is already taken \n",rollError);
	}else{ //Add new student to buffer
		FIFO_add_item(fifo_buf, &student);
		printf("[INFO] Student Details is added successfully \n");
		SMS_CountStudents(fifo_buf);
	}
}


/************************************************************************************
 * Function Name: SMS_AddStudentDetialFromFile
 * Description: Function to get the student first name ,second name
 * ,GPA and Courses id form text file
 ************************************************************************************/
void SMS_AddStudentDetialFromFile(FIFO_Buf_t *fifo_buf){
	Student_t student;					//to save student information
	Student_t *pTemp; 					//variable to loop in buffer
	boolean rollFlag;					//to check if roll number is taken
	uint32 count=0;						//counter will use in for loop
	//Open the file
	FILE* ptrFile=fopen("students_information.txt","r");
	printf("------------ SMS_AddStudentDetialFromFile -----------\n");
	//check if FIFO is not initialized
	if(fifo_buf==NULL){
		printf("[ERROR] Student buffer is not initialized \n");
		return;
	}
	//Check if file is exist
	if(ptrFile == NULL){
		printf("[ERROE] Unable to open file for reading.\n");
		return;
	}
	//Reading until the end of the file
	while(!feof(ptrFile)){
		pTemp=fifo_buf->tail;
		rollFlag=FALSE;
		//Check if buffer is full
		if(FIFO_is_full(fifo_buf)==FIFO_FULL){
			printf("[ERROR] Student buffer is full you can't add more student \n");
			return;
		}
		fscanf(ptrFile,"%s %s",student.firstName,student.secondName);
		fscanf(ptrFile,"%lu",&student.rollNum);
		while(pTemp!=fifo_buf->head){  			//Check if roll number is taken
			if(student.rollNum==pTemp->rollNum){
				//if the roll if is already taken
				printf("[ERROR] The Roll number %lu is already taken - Adding Failed\n", student.rollNum);
				// skip the remaining line
				fscanf(ptrFile, "%*[^\n]");
				rollFlag=TRUE;
				break;
			}
			pTemp++; //Move to Next Student
		}
		//if the roll number is taken skip the remaining line
		if(rollFlag == TRUE){
			continue;
		}
		fscanf(ptrFile,"%f",&student.GPA);
		fscanf(ptrFile,"%lu",&student.NumOfCousres);
		for(count=0;count<student.NumOfCousres;count++){
			fscanf(ptrFile,"%u",&student.CourseID[count]);
		}
		FIFO_add_item(fifo_buf, &student);
		printf("[INFO] The Roll Number %lu is added successfully \n",student.rollNum);
	}
	//Close the file
	fclose(ptrFile);
	printf("[INFO] Student Details is added successfully \n");
}

/************************************************************************************
 * Function Name: SMS_FindStudentByRollNumber
 * Description: Function to search for the student by its roll number
 ************************************************************************************/
void SMS_FindStudentByRollNumber(FIFO_Buf_t *fifo_buf){
	uint32 rollNum;					//to store the required roll number
	Student_t *pReqStudent=NULL;	//to get required student
	printf("------------ SMS_FindStudentByRollNumber -----------\n");
	//check if FIFO is not initialized or full
	if(fifo_buf==NULL){
		printf("[ERROR] Student buffer is not initialized \n");
		return;
	}
	//get the required student roll number
	printf("Enter The Roll Number of Student: ");
	scanf("%lu",&rollNum);
	/*function will assign address of required student in pReqStudent*/
	FIFO_get_item_by_roll(fifo_buf, rollNum,(Student_t**)&pReqStudent);
	if(pReqStudent == NULL){
		printf("[ERROR] Roll Number %lu not found\n",rollNum);
	}else{
		printf("The Student Details:\n");
		printStudentInfo(pReqStudent);
	}
}

/************************************************************************************
 * Function Name: SMS_FindStudentByFirstName
 * Description: Function to search for the student by its first name
 ************************************************************************************/
void SMS_FindStudentByFirstName(FIFO_Buf_t *fifo_buf){
	char ReqStName[20];		//to store required student first name
	Student_t *pCurStudent;		//to loop in student buffer
	uint8 checkName;			//to check if name is found
	boolean flag=FALSE;			//check if any name is found
	printf("------------ SMS_FindStudentByRollNumber -----------\n");
	//check if FIFO is not initialized or full
	if(fifo_buf==NULL){
		printf("[ERROR] Student buffer is not initialized \n");
		return;
	}
	//assign to first student in the buffer
	pCurStudent=fifo_buf->tail;
	printf("Enter The First Name of Student: ");
	scanf("%s",ReqStName);
	while(pCurStudent!=fifo_buf->head){
		//check if name is match
		//if name is match strcmpi return 0
		checkName=strcmpi(ReqStName,pCurStudent->firstName);
		if(checkName == 0){
			if(flag==FALSE){
				printf("The Student Details:\n");
				flag=TRUE;
			}
			//if name is match print student details
			printStudentInfo(pCurStudent);
			printf("\n");
		}
		pCurStudent++;	//Move to the next student
	}
	//check if name is not fount
	if(flag == FALSE){
		printf("[ERROR] First Name %s not found\n",ReqStName);
	}
}

/************************************************************************************
 * Function Name: SMS_FindStudentByFirstName
 * Description: Function to search for the student by its first name
 ************************************************************************************/
void SMS_FindStudentsRegisteredInCourse(FIFO_Buf_t *fifo_buf){
	Courses_ID_t course;			//to store the required course id
	Student_t *pCurStudent;			//to loop in student buffer
	uint32 i;						//counter used to loop in courses for each student
	uint32 count=0;					//count the number of student registered in course
	printf("------------ SMS_FindStudentsRegisteredInCourse -----------\n");
	//check if FIFO is not initialized or full
	if(fifo_buf==NULL){
		printf("[ERROR] Student buffer is not initialized \n");
		return;
	}
	pCurStudent=fifo_buf->tail; //assign first student in the buffer
	PrintCousresMap(); //print available course name
	//get the required course id
	printf("Enter The Course ID: ");
	scanf("%u",&course);
	//Check if course id is available
	if( (course > MAXCOURSESID) || (course<MINCOURSESID)){
		printf("ERROR COURSE ID!\n");
		return;
	}
	printf("The Students Registered in Course ");
	printCourseName(course);
	printf(":\n");
	//Loop until reach to last student
	while(pCurStudent != fifo_buf->head){
		//Check courses for each student
		for(i=0;i<pCurStudent->NumOfCousres;i++){
			//check if course id match
			if(course == pCurStudent->CourseID[i]){
				//Print information of student registered in the course
				count++;
				printf("Full Name   : %s %s\n",pCurStudent->firstName,pCurStudent->secondName);
				printf("Roll Number : %lu\n",pCurStudent->rollNum);
				printf("GPA         : %0.2f\n",pCurStudent->GPA);
			}
		}
		pCurStudent++; 	//Move to  the next student in the buffer
	}
	printf("[INFO] Total Number of Students Registered : %lu\n",count);
}

/************************************************************************************
 * Function Name: SMS_CountStudents
 * Description: Function to count registration students
 ************************************************************************************/
void SMS_CountStudents(FIFO_Buf_t *fifo_buf){
	if(fifo_buf==NULL){
		printf("[ERROR] Student buffer is not initialized \n");
		return;
	}
	printf("--------------------------------------------------\n");
	printf("The total number of student is %lu\n",fifo_buf->count);
	printf("You can add up to %lu students\n",fifo_buf->length);
	printf("You can add %lu more students\n",(fifo_buf->length-fifo_buf->count));
	printf("--------------------------------------------------\n");
}

/************************************************************************************
 * Function Name: SMS_DeleteStudent
 * Description: Function to delete student from the system
 ************************************************************************************/
void SMS_DeleteStudent(FIFO_Buf_t *fifo_buf){
	uint32 rollNum;					//to store the required roll number
	FIFO_Status status;
	printf("------------ SMS_DeleteStudent -----------\n");
	//check if FIFO is not initialized or full
	if(fifo_buf==NULL){
		printf("[ERROR] Student buffer is not initialized \n");
		return;
	}
	//get the required student roll number
	printf("Enter The Roll Number of Student: ");
	scanf("%lu",&rollNum);
	/*function will find student by roll number then remove it*/
	status=FIFO_delete_item_by_roll(fifo_buf, rollNum);
	/*Check status of operation*/
	switch(status){
	case FIFO_NULL:
		printf("[ERROR] The Roll Number is Not Found\n");
		break;
	case FIFO_EMPTY:
		printf("[ERROR] The Student Buffer is Empty\n");
		break;
	case FIFO_NO_ERROR:
		printf("[INFO] The Roll Number %lu is Removed Successfully\n",rollNum);
		break;
	default:
		break;
	}
}

/************************************************************************************
 * Function Name: SMS_UpdateStudent
 * Description: Function to update the information of student
 ************************************************************************************/
void SMS_UpdateStudent(FIFO_Buf_t *fifo_buf){
	uint32 rollNum;					//to store the required roll number
	Student_t *pReqStudent=NULL;	//to get required student
	Student_t *pTemp;				//used to loop to check if roll number already taken
	SMS_updata_options_t option;					//to store update option number
	uint32 newRoll;					//to store the new roll number
	boolean rollFlag=FALSE;			//to check if roll number is taken
	printf("------------ SMS_UpdateStudent -----------\n");
	//check if FIFO is not initialized or full
	if(fifo_buf==NULL){
		printf("[ERROR] Student buffer is not initialized \n");
		return;
	}
	pTemp=fifo_buf->tail;
	//get the required student roll number
	printf("Enter The Roll Number of Student: ");
	scanf("%lu",&rollNum);
	/*function will assign address of required student in pReqStudent*/
	FIFO_get_item_by_roll(fifo_buf, rollNum,&pReqStudent);
	if(pReqStudent == NULL){
		printf("[ERROR] Roll Number %lu not found\n",rollNum);
		return;
	}
	printf("Update Student Details of Student With Roll Number %lu \n",rollNum);
	/*Update SubProgram*/
	while(1){
		printf("1.Update First Name\n");
		printf("2.Update Second Name\n");
		printf("3.Update Roll Number\n");
		printf("4.Update GPA\n");
		printf("5.Update Courses\n");
		printf("6.Back to Main Options\n");
		printf("Enter Update Option Number: ");
		scanf("%u",&option);
		switch(option){
		case SMS_UPDATE_FIRST_NAME:
			printf("Enter the New First Name: ");
			scanf("%s",pReqStudent->firstName);
			printf("[INFO] First Name is Updated Successfully\n");
			break;
		case SMS_UPDATE_SECOND_NAME:
			printf("Enter the New Second Name: ");
			scanf("%s",pReqStudent->secondName);
			printf("[INFO] Second Name is Updated Successfully\n");
			break;
		case SMS_UPDATE_ROLL_NUMBER:
			printf("Enter the New Roll Number: ");
			scanf("%lu",&newRoll);
			while(pTemp!=fifo_buf->head){  			//Check if roll number is taken
				if(newRoll ==pTemp->rollNum){
					rollFlag = TRUE;
					break;
				}
				pTemp++;		//Move to next student
			}
			if(rollFlag == FALSE){ //if roll number is not taken update it
				pReqStudent->rollNum=newRoll;
				printf("[INFO] Roll Number is Updated Successfully\n");
			}else{
				printf("[ERROE] Roll Number is Already Taken - Update Failed\n");
			}
			break;
		case SMS_UPDATE_GPA:
			printf("Enter the New GPA: ");
			scanf("%f",&pReqStudent->GPA);
			printf("[INFO] GPA is Updated Successfully\n");
			break;
		case SMS_UPDATE_COURSES:
			UpdataCourses(pReqStudent);
			break;
		case SMS_UPDATA_BACK:
			break;
		default:
			printf("[ERROE] WRONG UPDATE OPTION NUMBER!\n");
		}
		if(option==SMS_UPDATA_BACK){
			break;
		}
	}
}

/************************************************************************************
 * Function Name: SMS_displayAllInformation
 * Description: Function to update the information of student
 ************************************************************************************/
void SMS_displayAllInformation(FIFO_Buf_t *fifo_buf){
	//check if FIFO is not initialized or full
	if(fifo_buf==NULL){
		printf("[ERROR] Student buffer is not initialized \n");
		return;
	}
	Student_t *pTemp=fifo_buf->tail;
	uint32 i;
	printf("---------------- Display All Information ---------------\n");
	for(i=0;i<fifo_buf->count;i++){
		printf("\nStudent %lu:\n",i+1);
		printStudentInfo(pTemp);
		pTemp++;
	}
	SMS_CountStudents(fifo_buf);
}

/************************************************************************************
 * Function Name: PrintCousresMap
 * Description: Function to print available courses
 ************************************************************************************/
static void PrintCousresMap(){
	printf("Available Courses:\n");
	printf("(1) Math1      (2) Math2     (3) Programming\n");
	printf("(4) Mechanics  (5) Physics   (6) Electronics\n");
	printf("(7) Design     (8) Control   (9) Robotics\n");
}

/************************************************************************************
 * Function Name: printStudentInfo
 * Description: Function to print student information
 ************************************************************************************/
static void printStudentInfo(Student_t const *st){
	uint32 i;
	printf("Full Name   : %s %s\n",st->firstName,st->secondName);
	printf("Roll Number : %lu\n",st->rollNum);
	printf("GPA         : %0.2f\n",st->GPA);
	printf("Courses: ");
	for(i=0;i<st->NumOfCousres;i++){
		printCourseName(st->CourseID[i]);
	}
	printf("\n");
}

/************************************************************************************
 * Function Name: printCourseName
 * Description: Function to print course name by its id
 ************************************************************************************/
static void printCourseName(uint32 couresID){
	switch(couresID){
	case Math1:
		printf("(1) Math1 ");
		break;
	case Math2:
		printf("(2) Math2 ");
		break;
	case Programming:
		printf("(3) Programming ");
		break;
	case Mechanics:
		printf("(4) Mechanics ");
		break;
	case Physics:
		printf("(5) Physics ");
		break;
	case Electrnoics:
		printf("(6) Electronics ");
		break;
	case Design:
		printf("(7) Design ");
		break;
	case Control:
		printf("(8) Control ");
		break;
	case Robotics:
		printf("(9) Robotics ");
		break;
	}
}
/************************************************************************************
 * Function Name: UpdataCourses
 * Description: Function to update course for student
 ************************************************************************************/
static void UpdataCourses(Student_t *student){
	SMS_updata_options_t option;		//to store update option
	Courses_ID_t CourseID;				//to store the requried course id
	uint32 i;							//to loop in course for each student
	printf("1. Add Course\n");
	printf("2. Delete Course\n");
	printf("Enter Option: ");
	scanf("%u",&option);
	switch(option){
	case SMS_UPDATE_ADD_COURSE:
		PrintCousresMap();
		printf("Enter The New Course ID: ");
		scanf("%u",&CourseID);
		//check if course id is available
		if(CourseID>MAXCOURSESID || CourseID <MINCOURSESID){
			printf("[ERROR] WRONG COURSE ID! - Update Failed\n");
		}else{ //Add new course
			student->CourseID[student->NumOfCousres]=CourseID;
			student->NumOfCousres++;
			printf("[INFO] The New Course is Added Successfully\n");
		}
		break;
	case SMS_UPDATE_DELETE_COURSE:
		//display the student's courses
		printf("Courses: ");
		for(i=0;i<student->NumOfCousres;i++){
			printCourseName(student->CourseID[i]);
		}
		//Get the required course id
		printf("\nEnter The Course ID That You Want to Delete: ");
		scanf("%u",&CourseID);
		//check if student register in this course
		for(i=0;i<student->NumOfCousres;i++){
			if(CourseID ==student->CourseID[i]){
				break;
			}
		}
		if(i == student->NumOfCousres ){
			printf("[ERROE] Course ID is Not Found - Update Failed\n");
		}else{	//delete the course
			for(i=0;i<(student->NumOfCousres-1);i++){
				student->CourseID[i]=student->CourseID[i+1];
			}
			student->NumOfCousres--;
			printf("[INFO] The Course is Deleted Successfully\n");
		}
		break;
	default:
		printf("[ERROE] WRONG UPDATE OPTION NUMBER!\n");
		break;
	}
}
