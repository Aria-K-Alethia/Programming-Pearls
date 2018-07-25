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
	COLUMN 11 SORTING
	This column discussed two kind of sorting methods: insert sort and quick sort

	Insertion sort is one of the most direct and simple sort method to consider,
	also it is easy to implement and fast to run, with O(n^2) in the worst cases,

	Quick sort is the most common and fast algorithm in sorting,
	Its expected time complexity is O(nlogn), bad implementation would make it to O(n^2)
	But we can fix this problem.
	Although we know the time complexity of heap sort is also O(nlogn), but in general,
	quick sort is faster.

	Quick sort is faster, cause it not only find a proper position for one elem, but also find the
	ordering relation between rest elements in one cycle.

	PROBLEMs
	2.  quick_sort3, a updated version of quick sort1
	5.  bit string sort algorithm, T(n) = O(nlog(maxlength)), similar to quick sort
	6.  selection sort and shell sort, I would not implement selection sort, cause it is a 
        naive version of heap sort
    11. fat pivot partition, this algorithm is too difficult to implement and not be recommended
	13. the better selection of pivot, this is not implemented, but we should know that if the
	    pivot is a random, the expected TC is O(nlogn), and if the pivot is median, the TC
	    in worst case is O(nlogn)
	
	
*/

int min(int a, int b)
{
	return a > b ? b : a;
}

template <class T> void myswap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

void myswap2(int arr[], int a, int b, int n)
{
	int temp;
	for(int i = 0 ; i < n ; ++i){
		temp = arr[a+i];
		arr[a+i] = arr[b+i];
		arr[b+i] = temp;
	}
}

void insert_sort1(int arr[], int n)
{
	// first edition of insertion sort
	// invariant: arr[0...j] is sorted
	if(n == 1) return;
	for(int i = 1; i < n ; ++i){
		for(int j = i ; j > 0 && arr[j-1] > arr[j] ; --j)
			myswap(arr[j], arr[j-1]);
	}
}

void insert_sort2(int arr[], int n)
{
	// second edition of insertion sort,
	// we continuously move elem before x[i] to after until we find the pos to insert x[i]
	// this edition reduce some meaningless swaps
	int temp, j;
	if(n == 1) return;
	for(int i = 1 ; i < n ; ++i){
		temp = arr[i];
		for(j = i ; j > 0 && arr[j-1] > temp ; --j)
			arr[j] = arr[j-1];
		arr[j] = temp;
	}
}

// the 1st edition of qsort, O(n^2) when the array is in extreme case(identical, ordered, reversed)
void quick_sort1(int arr[], int l, int u)
{
	if(l >= u) return;
	int m = l;
	// here is the partition code
	for(int i = l+1 ; i <= u; ++i){
		/*
			invariant: arr[l...m-1] < arr[l] && arr[m...i] >= arr[l] 
		*/
		if(arr[i] < arr[m]){
		myswap(arr[++m], arr[i]);
		}
	}
	myswap(arr[m], arr[l]);
	// recur
	quick_sort1(arr, l, m-1);
	quick_sort1(arr, m+1, u);
}

// 2nd edition of qsort, repair the worst case problem in qsort1
void quick_sort2(int arr[], int l, int u)
{
	if(l >= u) return;
	// to avoid the worst case, we need to first swap arr[l] with a random elem in the array
	myswap(arr[l], arr[l + rand() % (u - l + 1)]);
	int i = l, j = u+1;
	while(1){
		/*
			invariant when i < j
			arr[l+1...i] < arr[l]
			arr[j...u] > arr[l]
		*/
		do{ i++; }while(arr[i] < arr[l]);
		do{ j--; }while(arr[j] > arr[l]);
		if(i > j) break;
	myswap(arr[i], arr[j]);
	}
	myswap(arr[l], arr[j]);
	quick_sort2(arr, l, j - 1);
	quick_sort2(arr, j + 1, u);
}

// 3nd edition of qsort1, more faster, less comparision, use sentinel
// but still has the worst case problem
void quick_sort3(int arr[], int l, int u)
{
	if(l >= u) return;
	myswap(arr[l], arr[l + rand() % (u - l + 1)]);
	int m, i;
	m = i = u+1;
	do{
		/*
			invariant: arr[m...u] >= arr[l] && arr[i...m] < arr[l] 
		*/
		while(arr[--i] < arr[l]);
		myswap(arr[--m], arr[i]);
	}while(i != l);
}

typedef struct BitString
{
	int length; // length of bitstring
	char* bit;  // bit string, char in bit should only be 1 or 0
}bitstring;


void bit_sort(bitstring arr[], int l, int u, int depth)
{
	/*
		overview:
			arr: the bitstring array
			l: low range
			u: upper range
			depth: current position
	*/
	if(l >= u) return;
	for(int i = l; i <= u ; ++i){
		// depth 0 means length 1, if length < depth + 1, no need to sort them
		if(arr[i].length < depth + 1)
			myswap(arr[i], arr[l++]);
	}
	int m = l;
	for(int i = l ; i <= u ; ++i){
		// invariant: arr[l...m-1][depth] == 0 && arr[m...u][depth] == 1
		if(arr[i].bit[depth] == 0){
			myswap(arr[i], arr[m++]);
		}
	}
	bit_sort(arr, l, m - 1, depth + 1);
	bit_sort(arr, m, u, depth + 1);
}

// shell sort: a advanced insertion sort, i.e. diminishing increment sort
void shell_sort(int arr[], int l, int u)
{
	int H[11]  = {1,5,19,41,109,209,505,929,2161,3905,8929};
	int size = u - l + 1, i, w, temp;
	// find the gap 
	for(i = 10 ; i >= 0 ; --i){
		if(H[i] < size)
			break;
	}
	// for all gap
	for(int j = i ;  j >= 0 ; --j){
		// insertion sort for arr[k, k+w, k+2w...]
		w = H[j];
		// for each column
		for(int k = 0 ; k < w ; ++k){
			for(int t = l + k + w; t <= u ; t += w){
				temp = arr[t];
				int x;
				for(x = t - w ; x >= l && arr[x] > temp; x -= w){
					arr[x + w] = arr[x];
				}
				arr[x + w] = temp; 
			}
		}
	}
}

// fat pivot partition for an advanced quicksort
// here we set arr[l] be pivot
void quick_sort4(int arr[], int l, int u)
{
	int a,b,c,d,t;
	// invariant: arr[l..a-1] == pivot && arr[a...b] < pivot
	// 			  && arr[c...d] > pivot && arr[d+1...u] == pivot
	if(l >= u) return;
	myswap(arr[l], arr[l + rand() % (u - l + 1)]);
	a = l + 1;
	b = l;
	c = u + 1;
	d = u;
	t = arr[l];
	while(1){
		do{ b++; }while(arr[b] < arr[l]);
		do{ c--; }while(arr[c] > arr[l]);
		if(b > c) break;
		if(arr[b] == arr[l] && arr[c] == arr[l]){
			myswap(arr[b], arr[a++]);
			myswap(arr[c], arr[d--]);
		}
		else if(arr[b] == arr[l] && arr[c] < arr[l]){
			myswap(arr[b], arr[c]);
			myswap(arr[c], arr[d--]);
		}
		else if(arr[b] > arr[l] && arr[c] == arr[l]){
			myswap(arr[c], arr[b]);
			myswap(arr[b], arr[a++]);
		}
		else{
			myswap(arr[b], arr[c]);
		}
	}
	int n;
	n = min(a - l, c - a + 1);
	myswap2(arr, l , c - n + 1, n);
	n = min(u - d, d - b + 1);
	myswap2(arr, b, u - n + 1, n);
	quick_sort4(arr, l, c - a + l);
	quick_sort4(arr, u - d + b, u);
}