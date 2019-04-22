#include <stdio.h>
#include "plist.h"
#include <time.h>

void main(){
	int n,k;
	plist p_bs,p_ss,p_is,p_qs,p_ms,p_tim;
	init_plist(&p_bs);
	init_plist(&p_ss);
	init_plist(&p_is);
	init_plist(&p_qs);
	init_plist(&p_ms);
	init_plist(&p_tim);
	scanf("%d\n",&n);
	printf("Sorting comparison for random input of %d integers:\n",n);
	for(int i=0;i<n;i++){
		scanf("%d\n",&k);
		append(&p_bs,k);
		append(&p_ss,k);
		append(&p_is,k);
		append(&p_qs,k);
		append(&p_ms,k);
		append(&p_tim,k);
	}
	double time_taken;
	clock_t t;
	t = clock();
	BubbleSort(&p_bs);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Bubble Sort    : %f sec\n",time_taken);
	t = clock();
	SelectionSort(&p_ss);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Selection Sort : %f sec\n",time_taken);
	t = clock();
	InsertionSort(&p_is);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Insertion Sort : %f sec\n",time_taken);
	t = clock();
	TimSort(&p_tim);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Timsort        : %f sec\n",time_taken);
	t = clock();
	MergeSort(&p_ms);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Mergesort      : %f sec\n",time_taken);
	t = clock();
	QuickSort(&p_qs);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Quicksort      : %f sec\n",time_taken);
}