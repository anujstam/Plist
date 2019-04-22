/*
 * Developed by Anuj Sanjay Tambwekar
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct{
	int size;
	int min;
	int max;
	int* list;
	int sorted;
}plist;

void init_plist(plist* p);
void append(plist* p, int n);
void display(plist p);
void push(plist* p, int n);
void enqueue(plist* p, int n);
void del(plist* p, int index);
int pop(plist* p);
int pop_verbose(plist* p, int v);
void extend(plist* p, int count, ...);
void checkminmax(plist* p);
void movemem(int* src, int* dest, int dst_index, int src_index, int num);
void insert(plist* p, int val, int index);
void InsertionSort(plist* p);
void merge(plist* p, int l, int m, int r);
void insertionSortTim(plist* p, int left, int right);
void TimSort(plist* p);
void BubbleSort(plist* p);
int checksorted(plist p);
int search(plist p, int val);
int binsearch(plist p, int l, int r, int val);
int seqsearch(plist p, int val);
void SelectionSort(plist* p);
void MergeSortLims(plist* p, int l, int r);
void MergeSort(plist* p);
void plist_merge(plist* p, int l, int m, int r);
int partition (plist* p, int l, int h);
void QuickSortLims(plist* p, int low, int high);
void QuickSort(plist* p);
void quickSortIterative (plist* p, int l, int h);
void qsi(plist* p);
void reverse(plist* p);
int plist_sum(plist p);

void init_plist(plist* p){
	p->size = 0;
	p->min = -1;
	p->max = -1;
	p->sorted = 1;
	p->list = NULL;
}

void append(plist* p, int n){
	if (p->size == 0){
		p->list = malloc(sizeof(int)*1);
		p->list[0] = n;
		p->min = n;
		p->max = n;
		p->size = 1;
	}
	else{
		int* temp = realloc(p->list,sizeof(int)*(p->size + 1));
		if (temp != NULL){
			p->list = temp;
			p->list[p->size++] = n;
			if (p->min>n){
				p->min = n;
			}
			if (p->max < n){
				p->max = n;
			}
			else{
				p->sorted = 0;
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
		int* temp = realloc(p->list,sizeof(int)*(p->size + count));
		if (temp != NULL){
			p->list = temp;
			for (int i = 0; i<count; i++){
				int n = va_arg(args, int);
				p->list[p->size++] = n;
				if (p->min>n){
					p->min = n;
				}
				if (p->max < n){
					p->max = n;
				}
				else{
					p->sorted = 0;
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
		p->min = p->list[0];
		p->max = p->list[0];
		for (int i=0;i<p->size;i++){
			if (p->list[i]>p->max){
				p->max = p->list[i];
			}
			if (p->list[i]<p->min){
				p->min = p->list[i];
			}
		}
	}
}

void del(plist* p, int index){
	if (index<0 || index>p->size-1|| p->size == 0){
		return;
	}
	else{
		int n = p->list[index];
		int* temp = realloc(p->list,sizeof(int)*(p->size));
		if (temp != NULL){
			int ct = 0;
			for (int i=0;i<p->size;i++){
				if (i!=index){
					temp[ct++] = p->list[i];
				}
			}
			p->list = temp;
			p->size -=1;
			checkminmax(p);
			p->sorted = checksorted(*p);
		}
		else{
			printf("Fatal realloc\n");
		}
	}
}

int pop_verbose(plist* p, int v){
	if (p->size != 0){
		int n = p->list[p->size -1];
		int* temp = realloc(p->list,sizeof(int)*(p->size - 1));
		if (temp != NULL){
			p->list = temp;
			p->size-=1;
			if (p->min == n){
				p->min = p->list[0]; 
				for (int i=0;i<p->size;i++){
					if (p->list[i]<p->min){
						p->min = p->list[i];
					}
				}
			}
			if (p->max == n){
				p->max = p->list[0]; 
				for (int i=0;i<p->size;i++){
					if (p->list[i] > p->max){
						p->max = p->list[i];
					}
				}
			}
			p->sorted = checksorted(*p);
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
		printf("%d",p.list[i]);
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
	int* temp = realloc(p->list,sizeof(int)*(p->size + 1));
	p->size += 1;
	int ct_og = 0;
	int ct_new = p->size-1;
	if (temp != NULL){
			while(ct_new > index){
				if (ct_new != index){
					temp[ct_new] = p->list[ct_new-1];
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
			p->list = temp;
			p->sorted = checksorted(*p);
	}
	else{
		printf("Fatal Plist Realloc error. Plist array was set to NULL\n");
	}
}

void InsertionSort(plist* p){
	if (p->sorted == 0){
		int i, key, j; 
		for (i = 1; i < p->size; i++) { 
			key = p->list[i]; 
			j = i - 1; 
			while (j >= 0 && p->list[j] > key) { 
				p->list[j + 1] = p->list[j]; 
				j = j - 1; 
			} 
			p->list[j + 1] = key; 
		}
		p->sorted = 1;
	}
}

void insertionSortTim(plist* p, int left, int right) { 
    for (int i = left + 1; i <= right; i++){ 
        int temp = p->list[i]; 
        int j = i - 1; 
        while (p->list[j] > temp && j >= left){ 
            p->list[j+1] = p->list[j]; 
            j--; 
        } 
        p->list[j+1] = temp; 
    } 
} 

void merge(plist* p, int l, int m, int r){ 
    int len1 = m - l + 1, len2 = r - m;
	if (len2<0){
		len2 = -1*len2;
	}
	//printf("len1: %d len2: %d\n",len1,len2);
    int left[len1], right[len2]; 
    for (int i = 0; i < len1; i++){
		left[i] = p->list[l + i];
	}
    for (int i = 0; i < len2; i++){ 
        right[i] = p->list[m + 1 + i];
	}		
    int i = 0; 
    int j = 0; 
    int k = l;
	//printf("LR Done /");
    while (i < len1 && j < len2){ 
        if (left[i] <= right[j]){ 
            p->list[k] = left[i]; 
            i++; 
        } 
        else{ 
            p->list[k] = right[j]; 
            j++; 
        } 
        k++; 
    }
	//printf("One done/");
    while (i < len1){ 
        p->list[k] = left[i]; 
        k++; 
        i++;
	} 
    while (j < len2){ 
        p->list[k] = right[j]; 
        k++; 
        j++; 
    }
	//printf("Other done\n");
}

int min(int a,int b){
	if (a<b){
		return a;
	}
	return b;
}

void TimSort(plist* p){
	if (p->sorted == 0){
		int RUN = 32;
		int n = p->size;
		int offset = n%RUN;
		n -= offset;
		int count = 1;
		/*
		for(int i=n;i<p->size;i++){
				printf("%d,",p->list[i]);
			}
			printf("\n");
		*/
		if (offset>0){
			insertionSortTim(p, n, p->size-1);
		}
		for (int i = 0; i < n; i+=RUN){
			//printf("RUN NUMBER:%d\n",count++);
			insertionSortTim(p, i, i+31);
		}
		/*
		for(int i=n;i<p->size;i++){
				printf("%d,",p->list[i]);
			}
			printf("\n");
		*/
		int rc =0;
		for (int run_size = RUN; run_size < n; run_size = 2*run_size){ 
			//printf("RUN SIZE: %d\n",run_size);
			int sub_count = n/run_size;
			for (int left = 0; left < n; left += 2*run_size){ 
				int mid = left + run_size - 1; 
				int right = min((left + 2*run_size - 1), (n-1));
				plist_merge(p,left,mid,right);	
			}
			if (sub_count%2==1){
				n-=run_size;
				plist_merge(p,n,n+run_size-1,p->size-1);
			}
		}
		plist_merge(p,0,n-1,p->size-1);
		p->sorted = 1;
	}
}

void BubbleSort(plist* p){
	if (p->sorted == 0){
		int n = p->size;
		int temp;
		int noswap = 1;
		for(int i=0;i<n;i++){
			noswap = 1;
			for(int j=0;j<n-1-i;j++){
				if (p->list[j]>p->list[j+1]){
					noswap = 0;
					temp = p->list[j];
					p->list[j] = p->list[j+1];
					p->list[j+1] = temp;
				}
			}
			if (noswap == 1){
				break;
			}
		}
		p->sorted = 1;
	}
}

int checksorted(plist p){
	int lim = p.size;
	for(int i=0;i<lim-1;i++){
		if (p.list[i]>p.list[i+1]){
			return 0;
		}
	}
	return 1;
}

int seqsearch(plist p, int val){
	for (int i=0;i<p.size;i++){
		if (p.list[i] == val){
			return i;
		}
	}
	return -1;
}

int binsearch(plist p, int l, int r, int val){ 
    if (r >= l){ 
        int mid = l + (r - l) / 2; 
        if (p.list[mid] == val){ 
            return mid;
		}
        if (p.list[mid] > val){
            return binsearch(p, l, mid - 1, val); 
		} 
        return binsearch(p, mid + 1, r, val); 
    } 
    return -1; 
} 

int search(plist p, int val){
	if (p.sorted == 1){
		return binsearch(p,0,p.size-1,val);
	}
	else{
		return seqsearch(p,val);
	}
}

void SelectionSort(plist* p){
	int min;
	int id;
	for (int i=0;i<p->size;i++){
		min = p->list[i];
		id = i;
		for(int j=i+1;j<p->size;j++){
			if (p->list[j]<min){
				min = p->list[j];
				id = j;
			}
		}
		p->list[id] = p->list[i];
		p->list[i] = min;
	}
	p->sorted = 1;
}

void plist_merge(plist* p, int l, int m, int r){ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m;
	if (n2<0){
		n2 = -n2;
	}
    int L[n1], R[n2]; 
    for (i = 0; i < n1; i++){ 
        L[i] = p->list[l + i];
	}		
    for (j = 0; j < n2; j++){
        R[j] = p->list[m + 1+ j]; 
	}
    i = 0; 
    j = 0;
    k = l;
    while (i < n1 && j < n2){ 
        if (L[i] <= R[j]){ 
            p->list[k] = L[i]; 
            i++; 
        } 
        else{ 
            p->list[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1){ 
        p->list[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2){ 
        p->list[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void MergeSortLims(plist* p, int l, int r) { 
    if (l < r) { 
        int m = l+(r-l)/2; 
        MergeSortLims(p, l, m); 
        MergeSortLims(p, m+1, r); 
        plist_merge(p, l, m, r); 
    } 
}

void MergeSort(plist* p){
	MergeSortLims(p, 0, p->size -1);
	p->sorted = 1;
}

void QuickSortLims(plist* p, int low, int high){ 
    if (low < high) { 
        int part_index = partition(p, low, high); 
        QuickSortLims(p, low, part_index - 1); 
        QuickSortLims(p, part_index + 1, high); 
    } 
}

void QuickSort(plist* p){
	
	if (p->size <= 64000){
		QuickSortLims(p,0,p->size-1);
	}
	else{
		qsi(p);
	}
}

int plist_sum(plist p){
	int s = 0;
	for (int i=0;i<p.size;i++){
		s+=p.list[i];
	}
	return s;
}

  
/* This function is same in both iterative and recursive*/
int partition (plist* p, int l, int h){ 
    int x = p->list[h]; 
    int i = (l - 1); 
  
    for (int j = l; j <= h- 1; j++) 
    { 
        if (p->list[j] <= x) 
        { 
            i++;
			int temp = p->list[i];
			p->list[i] = p->list[j];
			p->list[j] = temp;
            //swap (&arr[i], &arr[j]); 
        } 
    } 
    //swap (&arr[i + 1], &arr[h]); 
	int temp = p->list[i+1];
	p->list[i+1] = p->list[h];
	p->list[h] = temp;
    return (i + 1); 
} 
void qsi(plist* p){
	quickSortIterative(p,0,p->size -1);
}
void quickSortIterative (plist* p, int l, int h) { 
    // Create an auxiliary stack 
    int stack[ h - l + 1 ]; 
  
    // initialize top of stack 
    int top = -1; 
  
    // push initial values of l and h to stack 
    stack[ ++top ] = l; 
    stack[ ++top ] = h; 
  
    // Keep popping from stack while is not empty 
    while ( top >= 0 ) 
    { 
        // Pop h and l 
        h = stack[ top-- ]; 
        l = stack[ top-- ]; 
  
        // Set pivot element at its correct position 
        // in sorted array 
        int piv = partition(p, l, h ); 
  
        // If there are elements on left side of pivot, 
        // then push left side to stack 
        if ( piv-1 > l ) 
        { 
            stack[ ++top ] = l; 
            stack[ ++top ] = piv - 1; 
        } 
  
        // If there are elements on right side of pivot, 
        // then push right side to stack 
        if ( piv+1 < h ) 
        { 
            stack[ ++top ] = piv + 1; 
            stack[ ++top ] = h; 
        } 
    } 
} 


void reverse(plist* p){
	int s = p->size;
	int temp;
	for (int i=0;i<s/2;i++){
		temp = p->list[i];
		p->list[i] = p->list[s-1-i];
		p->list[s-1-i] = temp;
	}
}

void make_set(plist* p){
	if (p->sorted == 1){
		int n = p->size;
		if (n==0 || n==1){ 
			return;
		}
		int temp[n];
		int j = 0; 
		for (int i=0; i<n-1; i++){
			if (p->list[i] != p->list[i+1]){				
				temp[j++] = p->list[i]; 
			}
		}
		temp[j++] = p->list[n-1]; 
		p->list = realloc(p->list,sizeof(int)*(j));
		for (int i=0; i<j; i++){
			p->list[i] = temp[i];
		}
		p->size = j;
	}
	else{
		int count = 0;
		int n = p->size;
		int temp[n];
		int j;
		int included;
		for(int i=0;i<n;i++){
			j=0;
			included = 0;
			while(j<count){
				if (p->list[i]==temp[j++]){
					included = 1;
					break;
				}
			}
			if (included == 0){
				temp[count++] = p->list[i];
			}
		}
		
		p->list = realloc(p->list,sizeof(int)*(count));
		for (int i=0; i<count; i++) {
			p->list[i] = temp[i];
			p->size = count;
		}
			
	}
				
}	