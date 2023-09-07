/******************************************************************************
 * Module: FIFO
 * File Name: fifo.c
 * Description: Source file for FIFO Data structure
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/
#include "fifo.h"
#include <stdio.h>
#include <stdlib.h>


/*******************************************************************************
 *                      Function Definition                                    *
 *******************************************************************************/

/************************************************************************************
 * Function Name: FIFO_init
 * Parameters (in):	FIFO_Buf_t - Pointer to FIFO buffer
 * 					buffer - pointer to data buffer
 * 					len - Length of data buffer
 * Return value: status of FIFO buffer
 * Description: Function to initialize FIFO buffer
 ************************************************************************************/
FIFO_Status FIFO_init(FIFO_Buf_t* fifo_buf,ELEMENT_TYPE *buffer,uint32 len){
	FIFO_Status status;
	if(buffer==NULL){
		status=FIFO_NULL;
	}else{
		fifo_buf->base=buffer;
		fifo_buf->head=buffer;
		fifo_buf->tail=buffer;
		fifo_buf->length=len;
		fifo_buf->count=0;
		status=FIFO_NO_ERROR;
	}
	return status;
}
/************************************************************************************
 * Function Name: FIFO_add_item
 *  * Parameters (in): 	fifo_buf - Pointer to FIFO buffer
 * 						date - pointer to the data that will be added
 * Description: Function to add item in FIFO buffer.
 ************************************************************************************/
FIFO_Status FIFO_add_item(FIFO_Buf_t* fifo_buf,const ELEMENT_TYPE *data){
	FIFO_Status status;
	//check if FIFO valid
	if(fifo_buf->base == NULL ||fifo_buf->head == NULL||fifo_buf->tail == NULL){
		status=FIFO_NULL;
		//Check if FIFO is full
	}else if(FIFO_is_full(fifo_buf) == FIFO_FULL){
		status=FIFO_FULL;
	}else{
		//Write data in FIFO buffer
		*(fifo_buf->head) = *data;
		fifo_buf->head++;
		fifo_buf->count++;
		status=FIFO_NO_ERROR;
	}
	return status;
}

/************************************************************************************
 * Function Name: FIFO_is_full
 * Parameters (in): fifo_buf - Pointer to FIFO buffer
 * Return value: status of FIFO buffer
 * Description: Function to check if FIFO is full.
 ************************************************************************************/
FIFO_Status FIFO_is_full(const FIFO_Buf_t* fifo_buf){
	FIFO_Status status;
	//Check FIFO is valid
	if(fifo_buf->base == NULL ||fifo_buf->head == NULL||fifo_buf->tail == NULL){
		status=FIFO_NULL;
		//Check if FIFO is full
	}else if(fifo_buf->count >= fifo_buf->length){
		status=FIFO_FULL;
	}else{
		status=FIFO_NO_ERROR;
	}
	return status;
}

/************************************************************************************
 * Function Name: FIFO_delete_item_by_roll
 * Parameters (in): fifo_buf - Pointer to FIFO buffer
 * 					roll - the roll number of item that will be deleted
 * Return value: status of FIFO buffer
 * Description: Function to delete item form buffer by its roll number
 ************************************************************************************/
FIFO_Status FIFO_delete_item_by_roll(FIFO_Buf_t* fifo_buf,const uint32 roll){
	FIFO_Status status;
	ELEMENT_TYPE *pStudent=NULL;
	//Check FIFO is valid
	if(fifo_buf->base == NULL ||fifo_buf->head == NULL||fifo_buf->tail == NULL){
		status=FIFO_NULL;
		//Check if FIFO is empty
	}else if(fifo_buf->count == 0){
		status=FIFO_EMPTY;
	}else{
		FIFO_get_item_by_roll(fifo_buf, roll, (Student_t**)&pStudent);
		if(pStudent==NULL){
			status=FIFO_NULL;
		}else{
			while(pStudent != (fifo_buf->head-1)){
				*pStudent=*(pStudent+1);
				pStudent++;
			}
			fifo_buf->head--;
			fifo_buf->count--;
			status=FIFO_NO_ERROR;
		}
	}
	return status;
}
/************************************************************************************
 * Function Name: FIFO_get_item_by_roll
 * Parameters (in): fifo_buf - Pointer to FIFO buffer
 * 					roll - the roll number of item that will be got
 * 					item - pointer to pointer to element to save address of item
 * Return value: status of FIFO buffer
 * Description: Function to get item form FIFO buffer by its roll number.
 ************************************************************************************/
FIFO_Status FIFO_get_item_by_roll(FIFO_Buf_t* fifo_buf,const uint32 roll,ELEMENT_TYPE **item){
	FIFO_Status status;
	ELEMENT_TYPE *pTemp=fifo_buf->tail;
	uint32 i;
	//Check FIFO is valid
	if(fifo_buf->base == NULL ||fifo_buf->head == NULL||fifo_buf->tail == NULL){
		status=FIFO_NULL;
		//Check if FIFO is empty
	}else if(fifo_buf->count == 0){
		status=FIFO_EMPTY;
	}else{
		//loop to find the student by its id
		for(i=0;i<fifo_buf->count;i++){
			//start from tail
			if(roll == pTemp->rollNum){
				*item=pTemp;
				break;
			}
			pTemp++;
		}
		status=FIFO_NO_ERROR;
	}
	return status;
}
