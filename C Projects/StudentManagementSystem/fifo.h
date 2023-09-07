 /******************************************************************************
 * Module: FIFO
 * File Name: fifo.c
 * Description: Header file for FIFO Data structure
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/

#ifndef FIFO_H_
#define FIFO_H_

#include "Platform_Types.h"
/*******************************************************************************
 *                             User Configuration                              *
 *******************************************************************************/

typedef enum {
	Math1=1,Math2,Programming,
	Mechanics,Physics,Electrnoics,
	Design,Control,Robotics
}Courses_ID_t;

typedef struct{
	char firstName[20];
	char secondName[20];
	uint32 rollNum;
	float32 GPA;
	Courses_ID_t CourseID[10];
	uint32 NumOfCousres;
}Student_t;

#define ELEMENT_TYPE Student_t

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/*Structure for FIFO buffer*/
typedef struct{
	uint32 length;
	uint32 count;
	Student_t* head;
	Student_t* base;
	Student_t* tail;
}FIFO_Buf_t;

/*Enumeration for different status of FIFO buffer*/

typedef enum{
	FIFO_NO_ERROR,
	FIFO_FULL,
	FIFO_NULL,
	FIFO_EMPTY
}FIFO_Status;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function to initialize FIFO buffer */
FIFO_Status FIFO_init(FIFO_Buf_t* fifo_buf,ELEMENT_TYPE *buffer,uint32 len);

/*Function to add item in FIFO buffer. */
FIFO_Status FIFO_add_item(FIFO_Buf_t* fifo_buf,const ELEMENT_TYPE *data);

/* Function to get item form FIFO buffer by its roll number. */
FIFO_Status FIFO_get_item_by_roll(FIFO_Buf_t* fifo_buf,const uint32 roll,ELEMENT_TYPE**item);

/* Function to delete item form buffer by its roll number */
FIFO_Status FIFO_delete_item_by_roll(FIFO_Buf_t* fifo_buf,const uint32 roll);

/* Function to check if FIFO is full */
FIFO_Status FIFO_is_full(const FIFO_Buf_t* fifo_buf);


#endif /* FIFO_H_ */
