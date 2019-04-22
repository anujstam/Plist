#include <stdio.h>
#include <stdlib.h>
#include "plist.h"

void main(){
	int run = 1;
	printf("Interactive menu for Plist!\n");
	printf("************************\n");
	printf("Enter:\n");
	printf("0 to display\n");
	printf("1 to append\n");
	printf("2 to pop\n");
	printf("3 to insert\n");
	printf("4 to delete\n");
	printf("5 to search\n");
	printf("6 to sort\n");
	printf("7 to show maximal element\n");
	printf("8 to show minimal element\n");
	printf("9 to show length\n");
	printf("10 to reduce to a set\n");
	printf("11 to calculate sum of elements\n");
	printf("12 to reverse\n");
	printf("13 to exit\n");
	printf("************************\n");
	plist p;
	init_plist(&p);
	printf("Plist is empty. Extending it with 10 values");
	extend(&p,10,100,110,6,5,120,90,5,120,130,220);
	printf("\nThe PList after extend is:\n");
	display(p);
	int choice;
	int temp;
	while(run==1){
		
		printf(">>>>:");
		scanf("%d",&choice);
		
		switch(choice){
			
			case 0:{
					display(p);
					break;
					}
					
			case 1:{
					printf("Enter value to append: ");
					scanf("%d",&temp);
					append(&p,temp);
					break;
					}
					
			case 2:{
					printf("%d popped\n",pop(&p));
					break;
					}
					
			case 3:{
					printf("Enter value to insert: ");
					scanf("%d",&temp);
					int temp2 = temp;
					printf("\nEnter index to insert at: ");
					scanf("%d",&temp);
					insert(&p,temp2,temp);
					break;
					}
					
			case 4:{
					printf("Enter index to delete: ");
					scanf("%d",&temp);
					del(&p,temp);
					break;
					}
					
			case 5:{
					printf("Enter value to search: ");
					scanf("%d",&temp);
					int res = search(p,temp);
					if (res==-1){
						printf("Value not found in Plist\n");
					}
					else{
						printf("Value found at index %d\n",res);
					}
					break;
					}
					
			case 6:{
					TimSort(&p);
					break;
					}
					
			case 7:{
					printf("Max:%d\n",p.max);
					break;
					}
					
			case 8:{
					printf("Min:%d\n",p.min);
					break;
					}
					
			case 9:{
					printf("Length:%d\n",p.size);
					break;
					}
					
			case 10:{
					make_set(&p);
					break;
					}
			
			case 11:{
					int res = plist_sum(p);
					printf("Sum:%d\n",res);
					break;
					}
					
			case 12:{
					reverse(&p);
					break;
					}
					
			case 13:{
					run = 0;
					break;
					}
					
			default:{
					run =0;
					break;
			}				
		}
	}
}