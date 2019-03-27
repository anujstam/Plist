typedef struct{
	int size;
	int min;
	int max;
	int* pyl;
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