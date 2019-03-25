typedef struct{
	int size;
	int min;
	int max;
	int* pyl;
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
void SortInsertion(plist* p);
void merge(plist* p, int l, int m, int r);
void insertionSort(plist* p, int left, int right);
void TimSort(plist* p);