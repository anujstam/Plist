#include <stdio.h>
#include <stdlib.h>
#include "plist.h"

void main(){
	int k,temp;
	plist p;
	init_plist(&p);
	scanf("%d",&k);
	for (int i=0;i<k;i++){
		scanf("%d",&temp);
		append(&p,temp);
	}
	printf("\nThe PList is:\n");
	//display(p);
	printf("The smallest element is %d\n",p.min);
	printf("The largest element is %d\n",p.max);
	extend(&p,5,100,110,120,90,130);
	printf("\nThe PList after extend is:\n");
	//display(p);
	printf("The smallest element is %d\n",p.min);
	printf("The largest element is %d\n",p.max);
	int lim = p.size;
	for (int i = 0;i<lim/2;i++){
		del(&p,0);
		//display(p);
	}
	printf("Inserts:\n");
	insert(&p,1234,2);
	//display(p);
	insert(&p,12345,0);
	//display(p);
	insert(&p,4321,p.size-2);
	//display(p);
	//printf("The sorted array:\n");
	//TimSort(&p);
	//display(p);
	for (int i=100;i>1;i--){
		append(&p,i);
	}
	display(p);
	printf("Sorted plist:\n");
	SortInsertion(&p);
	display(p);
}