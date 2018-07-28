/*
	Copyright (C) 2018 Aria-K-Alethia@github.com
	Overview:
		these code snippets are my practices
		of the book << Programming Pearls >>.
	Licence:
		MIT

	THE USER OF THIS CODE AGREES TO ASSUME ALL LIABILITY FOR THE USE OF THIS CODE.
	Any use of this code should display all the info above.
	
*/


/*
	COLUMN 14 HEAPS

	Overview:
		This column talks about Heap, a useful data structure which could find
		maximum or minimum in an array in O(logn) time.
		Heap relates to the famous algo heap sort(O(nlogn)) and a data structure
		Priority Queue.

		Heap is a kind of binary tree satisfying two property: order & shape
		Order property means all the child nodes are greater(less) than their parent node.
		Shape property means the child node always tries to find a left position of a parent,
		that means heap can be presented by an array.

		Two critical function for heap is siftup and siftdown
		For more details of these two functions, see the implementation below.

	PROBLEMS:
		2&3.an advanced version of siftdown(int heap[], int l, int u) see siftdown2
			also heap_sort2 using this siftdown, construct a heap in O(n) time.
		

	NOTE:
		I only implemented the min-heap.
*/

#define HEAP_PARENT(x) (x / 2)
#define HEAP_LEFT_CHILD(x) (2*x)
#define HEAP_RIGHT_CHILD(x) (2*x+1)
#define HEAP_NULL(x, n) (x < 1 || x > n)

void siftup(int heap[], int n)
{
	/*
		pre-condition:
			heap[1...n] is a heap, but heap[n] and its parents may not confirm the property
		post-condition:
			heap[1...n] is a heap
		params:
			n is the last elem's index of the heap
	*/
	int pos = n;
	int temp, p;
	p = HEAP_PARENT(pos);
	// set the sentinel
	heap[0] = heap[1];
	while(pos != 1 && heap[pos] < heap[p]){
		/*
			invariant: heap property is confirmed except maybe heap[pos] and its parents
		*/
		temp = heap[pos];
		heap[pos] = heap[p];
		heap[p] = temp;
		pos = p;
		p = HEAP_PARENT(pos);
	}
}

void siftdown(int heap[], int n)
{
	/*
		pre-condition:
			heap[1:n] is a heap, but heap[1] and its children may not confirm the property
			of heap
		post-condition:
			heap[1:n] is a heap
	*/
	int pos = 1,l,r,c, temp;
	do{
		/*
			invariant: heap[1...n] confirms the heap property, except maybe heap[pos] and its children
		*/
		l = HEAP_LEFT_CHILD(pos);
		r = HEAP_RIGHT_CHILD(pos);
		if(HEAP_NULL(l, n)) break;
		else c = l;
		if(!HEAP_NULL(r, n) && heap[l] > heap[r]) c = r;
		if(heap[pos] > heap[c]){
			temp = heap[pos];
			heap[pos] = heap[c];
			heap[c] = temp;
			pos = c;
		}
		else break;
	}while(true);

}

template <class T>
class PriorityQueue
{
public:
	PriorityQueue(int m){
		n = 0;
		maxsize = m;
		x = new T[m+1];
	}

	void insert(T t){
		if(n == maxsize) return;
		x[++n] = t;
		for(int i = n ; i > 1 && x[i] < x[p=i/2] ; i = p)
			swap(i, p);
	}
	T extractmin(){
		if(n < 1) return NULL;
		T ret = x[1];
		x[1] = x[n--];
		for(int i = 1 ; (c = 2*i) <= n ; i = c){
			if(c+1 <= n && x[c+1] < x[c]) c++;
			if(x[c] >= x[i]) break;
			else swap(c, i);
		}
		return ret;
	}
private:
	int n, maxsize;
	T* x;
	void swap(int i, int j){
		T temp = x[i]; x[i] = x[j]; x[j] = temp;
	}
};

// use priority queue to sort
template <class T>
void pqsort(T arr[], int n)
{
	PriorityQueue<T> pq(n);
	for(int i = 0 ; i < n ; ++i)
		pq.insert(arr[i]);
	for(int i = 0 ; i < n ; ++i)
		arr[i] = pq.extractmin();
}

/* 
	heap sort, better than the previous algorithm
	using only one array space to sort.

	Since we implement min-heap, the sort algo below will sort an array
	in decreasing order.

	NOTE arr start from arr[1], n should be the size of array, n+1 is the space of the array
*/

void heap_sort(int arr[], int n)
{
	int temp;
	for(int i = 2 ; i <= n ; ++i)
		siftup(arr, i);
	for(int i = n ; i > 1 ; --i){
		temp = arr[1];
		arr[1] = arr[i];
		arr[i] = temp;
		siftdown(arr, i - 1);
	}
}

//an advanced version of siftdown
void siftdown2(int heap[], int l, int u)
{
	/*
		pre-condition:
			heap[l+1:u] is a heap
			of heap
		post-condition:
			heap[l:n] is a heap
	*/
	int pos = l,lc,rc,c, temp;
	do{
		/*
			invariant: heap[1...n] confirms the heap property, except maybe heap[pos] and its children
		*/
		lc = HEAP_LEFT_CHILD(pos);
		rc = HEAP_RIGHT_CHILD(pos);
		if(HEAP_NULL(lc, u)) break;
		else c = lc;
		if(!HEAP_NULL(rc, u) && heap[lc] > heap[rc]) c = rc;
		if(heap[pos] > heap[c]){
			temp = heap[pos];
			heap[pos] = heap[c];
			heap[c] = temp;
			pos = c;
		}
		else break;
	}while(true);

}

// The 2nd version of heap sort, this algorithm can construct a heap in O(n) and sort in O(nlogn)
// but with a smaller constant
void heap_sort2(int arr[], int n)
{
	int temp;
	for(int i = n / 2; i >= 1 ; --i)
		siftdown2(arr, i, n);
	for(int i = n ; i >= 2 ; --i){
		temp = arr[i];
		arr[i] = arr[1];
		arr[1] = temp;
		siftdown2(arr, 1, i - 1);
	}
}

void col14_main()
{
	int arr[11] = {-1,4,5,8,9,6,1,2,3,7,10};
	heap_sort2(arr, 10);
	for(int i = 1 ; i <= 10 ; ++i){
		cout << arr[i] << " ";
	}
}