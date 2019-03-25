#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "plist.h"

void init_plist(plist* p){
	p->size = 0;
	p->min = -1;
	p->max = -1;
	p->pyl = NULL;
}

void append(plist* p, int n){
	if (p->size == 0){
		p->pyl = malloc(sizeof(int)*1);
		p->pyl[0] = n;
		p->min = n;
		p->max = n;
		p->size = 1;
	}
	else{
		int* temp = realloc(p->pyl,sizeof(int)*(p->size + 1));
		if (temp != NULL){
			p->pyl = temp;
			p->pyl[p->size++] = n;
			if (p->min>n){
				p->min = n;
			}
			if (p->max < n){
				p->max = n;
			}
		}
		else{
			printf("Fatal Plist Realloc error. Plist array was set to NULL\n");
		}
	}
}

void extend(plist* p, int count, ...){
		va_list args;
		va_start(args,count);
		int* temp = realloc(p->pyl,sizeof(int)*(p->size + count));
		if (temp != NULL){
			p->pyl = temp;
			for (int i = 0; i<count; i++){
				int n = va_arg(args, int);
				p->pyl[p->size++] = n;
				if (p->min>n){
					p->min = n;
				}
				if (p->max < n){
					p->max = n;
				}
			}
		}
		else{
			printf("Fatal Plist Realloc error. Plist array was set to NULL\n");
		}
		va_end(args);
}

int pop(plist* p){
	pop_verbose(p,0);
}

void push(plist* p, int n){
	append(p,n);
}

void enqueue(plist* p, int n){
	append(p,n);
}

void movemem(int* src, int* dest, int dst_index, int src_index, int num){
	int j = src_index;
	for (int i=dst_index;i<dst_index+num;i++){
		dest[i] = src[j++];
	}
}	

void checkminmax(plist* p){
	if (p->size == 0){
		init_plist(p);
	}
	else{
		p->min = p->pyl[0];
		p->max = p->pyl[0];
		for (int i=0;i<p->size;i++){
			if (p->pyl[i]>p->max){
				p->max = p->pyl[i];
			}
			if (p->pyl[i]<p->min){
				p->min = p->pyl[i];
			}
		}
	}
}

void del(plist* p, int index){
	if (index<0 || index>p->size-1|| p->size == 0){
		return;
	}
	else{
		int n = p->pyl[index];
		int* temp = realloc(p->pyl,sizeof(int)*(p->size));
		if (temp != NULL){
			int ct = 0;
			for (int i=0;i<p->size;i++){
				if (i!=index){
					temp[ct++] = p->pyl[i];
				}
			}
			p->pyl = temp;
			p->size -=1;
			checkminmax(p);
		}
		else{
			printf("Fatal realloc\n");
		}
	}
}

int pop_verbose(plist* p, int v){
	if (p->size != 0){
		int n = p->pyl[p->size -1];
		int* temp = realloc(p->pyl,sizeof(int)*(p->size - 1));
		if (temp != NULL){
			p->pyl = temp;
			p->size-=1;
			if (p->min == n){
				p->min = p->pyl[0]; 
				for (int i=0;i<p->size;i++){
					if (p->pyl[i]<p->min){
						p->min = p->pyl[i];
					}
				}
			}
			if (p->max == n){
				p->max = p->pyl[0]; 
				for (int i=0;i<p->size;i++){
					if (p->pyl[i] > p->max){
						p->max = p->pyl[i];
					}
				}
			}
			return n;
		}
		else{
			if (v==1){
				printf("Fatal Plist Realloc error. Plist array was set to NULL\n");
			}
			return -1;
		}
	}
	else{
		if (v==1){
			printf("Cannot Pop from empty Plist\n");
		}
		return -1;
	}
}

void display(plist p){
	printf("[");
	for (int i=0; i<p.size;i++){
		printf("%d",p.pyl[i]);
		if (i!=p.size-1){
			printf(",");
		}
	}
	printf("]\n");
}

void insert(plist* p, int val, int index){
	if (index<0){
		index = 0;
	}
	if (index>p->size){
		index = p->size;
	}
	int* temp = realloc(p->pyl,sizeof(int)*(p->size + 1));
	p->size += 1;
	int ct_og = 0;
	int ct_new = p->size-1;
	if (temp != NULL){
			while(ct_new > index){
				if (ct_new != index){
					temp[ct_new] = p->pyl[ct_new-1];
				}
				ct_new -= 1;
			}
			temp[index] = val;
			if (p->min>val){
				p->min = val;
			}
			if (p->max < val){
				p->max = val;
			}
		p->pyl = temp; 
		}
	else{
		printf("Fatal Plist Realloc error. Plist array was set to NULL\n");
	}
}

void SortInsertion(plist* p){ 
	int i, key, j; 
    for (i = 1; i < p->size; i++) { 
        key = p->pyl[i]; 
        j = i - 1; 
        while (j >= 0 && p->pyl[j] > key) { 
            p->pyl[j + 1] = p->pyl[j]; 
            j = j - 1; 
        } 
        p->pyl[j + 1] = key; 
    }
}

void insertionSort(plist* p, int left, int right) { 
    for (int i = left + 1; i <= right; i++){ 
        int temp = p->pyl[i]; 
        int j = i - 1; 
        while (p->pyl[j] > temp && j >= left){ 
            p->pyl[j+1] = p->pyl[j]; 
            j--; 
        } 
        p->pyl[j+1] = temp; 
    } 
} 

void merge(plist* p, int l, int m, int r){ 
    int len1 = m - l + 1, len2 = r - m; 
    int left[len1], right[len2]; 
    for (int i = 0; i < len1; i++){
		left[i] = p->pyl[l + i];
	}
    for (int i = 0; i < len2; i++){ 
        right[i] = p->pyl[m + 1 + i];
	}		
    int i = 0; 
    int j = 0; 
    int k = l; 
    while (i < len1 && j < len2){ 
        if (left[i] <= right[j]){ 
            p->pyl[k] = left[i]; 
            i++; 
        } 
        else{ 
            p->pyl[k] = right[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < len1){ 
        p->pyl[k] = left[i]; 
        k++; 
        i++;
	} 
    while (j < len2){ 
        p->pyl[k] = right[j]; 
        k++; 
        j++; 
    } 
}

int min(int a,int b){
	if (a<b){
		return a;
	}
	return b;
}

void TimSort(plist* p){ 
	int RUN = 32;
	int n = p->size;
    // Sort individual subarrays of size RUN 
    for (int i = 0; i < n; i+=RUN){ 
        insertionSort(p, i, min((i+31), (n-1)));
	}
    for (int size = RUN; size < n; size = 2*size){ 
        for (int left = 0; left < n; left += 2*size){ 
            int mid = left + size - 1; 
            int right = min((left + 2*size - 1), (n-1)); 
            merge(p, left, mid, right); 
        } 
    } 
}   