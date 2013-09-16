
// generic comparison function
typedef int (*CompareFunction) (void *a, void *b);

// Prototype for mysort()
void mysort( int n, int elementSize, void * array,
	     int ascending, CompareFunction compFunc );

