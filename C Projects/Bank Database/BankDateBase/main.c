/*
 * main.c
 *
 *  Created on: ???/???/????
 *      Author: Ehab Mohamed
 */


#include <stdio.h>
#include <stdlib.h>



typedef struct customer {
	int id;
	char name[50];
	char type[10];
	double cash;
	struct customer *next;
}customer;

customer *head=NULL;
int state=0;
int NumberOfCustomers=0;

void PrintMainOption(){
	printf("Please select one of the following options :\n\n");
	printf("1-Create New Customer \n");
	printf("2-Edit customer \n");
	printf("3-Print customer date  \n");
	printf("4-Delete customer \n");
	printf("5-Cash transfer from customer to another \n");
	printf("6-Print all customers date\n");
	printf("7-Exit \n");
}

void create_new_customer(){
	customer *New=(customer*)malloc(sizeof(customer));
	customer *Crruent=(customer*)malloc(sizeof(customer));
	char Error=0;
	New->id=NumberOfCustomers;
	printf("please enter the name : ");
	scanf(" %s",New->name);
	printf("please enter the cash : ");
	scanf("%lf",&New->cash);
	printf("please enter the type of card : ");
	scanf(" %s",New->type);
	do{
		Error=0;
		printf("please enter the id : ");
		scanf(" %d",&New->id);
		Crruent=head;
		for(int i=0;i<NumberOfCustomers;i++){
			if(New->id==Crruent->id){
				Error=1;
			}
			Crruent=Crruent->next;
		}
		if(Error==1){
			printf("id is already exsit , try again\n");
		}
	}while(Error!=0);
	if(head==NULL){
		head=New;;
	}else{
		Crruent=head;
		while(Crruent->next!=NULL){
			Crruent=Crruent->next;
		}
		Crruent->next=New;
	}
	NumberOfCustomers++;
}
void edit_customer(int id){
	customer *Customer=(customer*)malloc(sizeof(customer));
	customer *Crruent=(customer*)malloc(sizeof(customer));
	int option=0;
	char check=0;
	char Error=0;
	double money=0;
	Customer=head;
	while(id!=Customer->id){
		Customer=Customer->next;
		if(Customer==NULL){
			check=1;
			break;
		}
	}
	if(check==1){
		printf("id is not exsit\n");
	}else{
		while(1){
			printf("1-Edit name   \n");
			printf("2-Edit id     \n");
			printf("3-Edit Card type  \n");
			printf("4-Withdrawing money \n");
			printf("5-depositing money \n");
			printf("6-back to main option \n");
			scanf("%d",&option);
			switch(option){
			case 1:
				printf("please enter the New name : ");
				scanf(" %s",Customer->name);
				break;
			case 2:
				do{
					Error=0;
					printf("please enter the new id : ");
					scanf(" %d",&Customer->id);
					Crruent=head;
					for(int i=0;i<NumberOfCustomers;i++){
						if(Customer->id==Crruent->id){
							Error++;
						}
						Crruent=Crruent->next;
					}
					if(Error==2){
						printf("id is already exsit , try again\n");
					}
				}while(Error==2);
				break;
			case 3:
				printf("please enter the new type of card : ");
				scanf(" %s",Customer->type);
				break;
			case 4:
				do{
					Error=0;
					printf("please enter amount of money : ");
					scanf("%lf",&money);
					if(money>Customer->cash){
						Error=1;
						printf("The balance is not allowed, try again\n");
					}
				}while(Error!=0);
				printf("Successful!\n");
				Customer->cash=Customer->cash-money;
				printf("Your balance : %lf \n",Customer->cash);
				break;
			case 5:
				printf("please enter amount of money : ");
				scanf("%lf",&money);
				printf("Successful!\n");
				Customer->cash=Customer->cash+money;
				printf("Your balance : %lf \n",Customer->cash);
				break;
			case 6:
				break;
			}
			if(option==6){
				break;
			}
		}
	}

}

void Print_customer_date(int id){
	customer *Customer=(customer*)malloc(sizeof(customer));
	char check=0;
	Customer=head;
	while(id!=Customer->id){
		Customer=Customer->next;
		if(Customer==NULL){
			check=1;
			break;
		}
	}
	if(check==1){
		printf("id is not exsit\n");
	}else{
		printf("\n***************************************************************\n");
		printf("Name : %s\n",Customer->name);
		printf("id : %d\n",Customer->id);
		printf("Cash : %lf\n",Customer->cash);
		printf("Card Type : %s\n",Customer->type);
		printf("***************************************************************\n");
	}
}


void Print_all_customers_date(){
	customer *Customer=(customer*)malloc(sizeof(customer));
	char i=0;
	Customer=head;
	if(	Customer==NULL){
		printf("there is not customers \n");
	}else{
		printf("Number of customers = %d\n\n",NumberOfCustomers);
		while(Customer!=NULL){
			i++;
			printf("(%d)\n",i);
			printf("Name : %s\n",Customer->name);
			printf("id : %d\n",Customer->id);
			printf("Cash : %lf\n",Customer->cash);
			printf("Card Type : %s\n\n",Customer->type);
			Customer=Customer->next;
		}
	}
}



void Delete_customer(int id){
	customer *Customer=(customer*)malloc(sizeof(customer));
	customer *Pervious=(customer*)malloc(sizeof(customer));
	int Error=0;
	Customer=head;
	while(id!=Customer->id){
		Pervious=Customer;
		Customer=Customer->next;
		if(Customer==NULL){
			Error=1;
			break;
		}
	}
	if(Error==1){
		printf("id not exsit\n");
	}else{
		Pervious->next=Customer->next;
		free(Customer);
		NumberOfCustomers--;
		printf("delete successful\n");
	}
}

void cash_transter(int from_id,int to_id,double money){
	customer *from=(customer*)malloc(sizeof(customer));
	customer *to=(customer*)malloc(sizeof(customer));
	int error=0;
	from=head;
	to=head;
	while(from_id!=from->id){
		from=from->next;
		if(from==NULL){
			error=1;
			break;
		}
	}
	while(to_id!=to->id){
		to=to->next;
		if(to==NULL){
			error=2;
			break;
		}
	}
	if(error==1){
		printf("the transfer id is not exsit\n");
	}else if(error==2){
		printf("the reciver id is not exsit\n");
	}else{
		if(money>from->cash){
			printf("The balance is not allowed, try again\n");
		}else{
			to->cash+=money;
			from->cash-=money;
			printf("Transfer money successful\n");
		}

	}

}




int main(){
	setbuf(stdout,NULL);
	int option=0;
	int id=0;
	int from=0;
	int to=0;
	double money=0;
	while(1){
		switch(state){
		case 0:
			PrintMainOption();
			scanf("%d",&option);
			if(option>=1&&option<=6){
				state=option;
			}else{
				state=0;
				printf("Error! try again\n");
			}
			break;
		case 1:
			create_new_customer();
			state=0;
			break;
		case 2:
			printf("(-1) back to main options)\n Please enter customer id : ");
			scanf("%d",&id);
			if(id>=0){
				edit_customer(id);
			}
			state=0;
			break;
		case 3:
			printf("(-1) back to main options)\n Please enter customer id : ");
			scanf("%d",&id);
			if(id>=0){
				Print_customer_date(id);
			}
			state=0;
			break;
		case 4:
			printf("(-1) back to main options)\n Please enter customer id : ");
			scanf("%d",&id);
			if(id>=0){
				Delete_customer(id);
			}
			state=0;
			break;
		case 5:
			printf("(-1) back to main options)\n");
			printf("please enter sender id       : ");
			scanf("%d",&from);
			if(from>=0){
				printf("(-1) back to main options)\n");
				printf("please enter reciever id     : ");
				scanf("%d",&to);
				if(to>=0){
					printf("please enter amount of money : ");
					scanf("%lf",&money);
					cash_transter(from,to,money);
				}
			}
			state=0;
			break;
		case 6:
			Print_all_customers_date();
			state=0;
			break;
		case 7:
			break;
		}
		if(state==7){
			printf("Exit the program :)");
			break;
		}
	}
	return 0;
}
