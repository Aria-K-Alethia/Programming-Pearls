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
	COLUMN 9 CODE TUNING

	overview:
		Code Tuning is a technique which is in a low-level of improving
		programs efficiency. In some platform where the compiler is
		not so powerful, this technique can sometimes make a big
		difference in a pragram's performance.

		This column includes several tricks which effect performance and
		can not be usually noticed, including:
			1. a novel malloc method
			2. integer remainder
			3. macros and inline code, comparing to functions
			4. sequential search
			5. code tuning for binary search

	principles:
		1. we should know that every trick have its valid range.
		2. performance is just a part of program, not so important and not
		   so unimportant.
		3. profile is a good tool for detecting hot spots.
	
	inventory:
		1. the novel malloc function
			memory allocation is usually the bottleneck for some program
			pmalloc always uses less time than standard malloc
		2. sequential search
			the original program has two comparation in the loop(3.782sec)
			but sentinel program reduces the comparation to one(0.936sec)
			furthermore, the unrolling of loop could reduce the number of loop(0.699sec)
		3. tuned binary search
			the new binary search use a new invariant: x[l] < t && x[r] >= t && l < u
			this new invariant could help the function reduce one comparation
		4. program finding maximum value in an array using sentinel
			this is a safe max function, avoid to create a dummy max var.
		5. faster program to evaluate a polynomial with n multiplications
			*this program is not implemented because it is simple.*
*/

typedef struct Intchunk
{
	int a;
	int b;
	int c;
	int d;
}intchunk;

#define COL9_PROB1_N 100000
#define COL9_PROB1_HOLD 1000

#define COL9_PROB2_N 10000
#define COL9_PROB2_CYCLE 100
int col9_prob1_left;
char* col9_prob1_freenode;

void* col9_prob1_pmalloc(int size)
{
	if(size != sizeof(intchunk))
		return malloc(size);
	if(col9_prob1_left == 0){
		col9_prob1_freenode = (char*)malloc(COL9_PROB1_HOLD * sizeof(intchunk));
		col9_prob1_left = COL9_PROB1_HOLD;
	}
	void* ret = (void*)col9_prob1_freenode;
	col9_prob1_left--;
	col9_prob1_freenode += sizeof(intchunk);
	return ret;
}


void col9_prob1_main()
{
	// alloc 10000 intchunk, use standard malloc or pmalloc
	int n;
	intchunk* temp[COL9_PROB1_N];
	cout << "This is col9 prob1, input the algo to use(1 for standard, 2 for customized)" << endl;
	cin >> n;
	// alloc
	if(n == 1){
		for(int i = 0 ; i < COL9_PROB1_N; ++i)
			temp[i] = (intchunk*)malloc(sizeof(intchunk));
	}
	else if(n == 2){
		for(int i = 0 ; i < COL9_PROB1_N; ++i)
			temp[i] = (intchunk*)col9_prob1_pmalloc(sizeof(intchunk));
	}
	else{
		cout << "No such algo in col9 prob1..." << endl;
		exit(-1);
	}
	// free
	if(n == 1){
		for(int i = 0 ; i < COL9_PROB1_N; ++i)
		free(temp[i]);
	}
	else
		free(temp[0]);
}


int col9_prob2_naive(int arr[], int t, int n)
{
	for(int i = 0 ; i < n; ++i){
		if(arr[i] == t) return i;
	}
	return -1;
}

int col9_prob2_sentinel(int arr[], int t, int n)
{
	int hold, i=0;
	hold = arr[n-1];
	if(hold == t) return n-1;
	arr[n-1] = t;
	while(arr[i] != t) ++i;
	arr[n-1] = hold;
	if(i == n-1) return -1;
	return i;
}

int col9_prob2_unrolling(int arr[], int t, int n)
{
	int hold, i;
	hold = arr[n-1];
	if(hold == t) return n-1;
	arr[n-1] = t;
	for(i = 0 ;; i += 8){
		if(arr[i] == t){ break; }
		if(arr[i+1] == t){ i += 1; break; }
		if(arr[i+2] == t){ i += 2; break; }
		if(arr[i+3] == t){ i += 3; break; }
		if(arr[i+4] == t){ i += 4; break; }
		if(arr[i+5] == t){ i += 5; break; }
		if(arr[i+6] == t){ i += 6; break; }
		if(arr[i+7] == t){ i += 7; break; }
	}
	arr[n-1] = hold;
	if(i == n-1) return -1;
	return i;
}

void col9_prob2_main()
{
	// init the array and target
	int arr[COL9_PROB2_N];
	int target;
	srand((unsigned int)time(NULL));
	for(int i = 0 ; i < COL9_PROB2_N; ++i){
		arr[i] = rand() % 1000;
	}
	// read the algo number
	int n,out;
	cout << "This is col9 prob2, input the 1,2,3 to choose algo" << endl;
	cin >> n;
	// run the algo
	for(int i = 0 ; i < COL9_PROB2_CYCLE ; ++i){
		target = arr[rand() % COL9_PROB2_N];
		switch (n){
			case 1: out = col9_prob2_naive(arr, target, COL9_PROB2_N); break;
			case 2: out = col9_prob2_sentinel(arr, target, COL9_PROB2_N); break;
			case 3: out = col9_prob2_unrolling(arr, target, COL9_PROB2_N); break;
			default: cout << "No such algo in col9 prob2..." << endl; exit(-1);
		}
		// check the correctness
		assert(arr[out] == target);
	}
	// check for unknown elem
	out = col9_prob2_unrolling(arr, -1, COL9_PROB2_N);
	assert(out == -1);
	out = col9_prob2_sentinel(arr, -1, COL9_PROB2_N);
	assert(out == -1);
	out = col9_prob2_naive(arr, -1, COL9_PROB2_N);
	assert(out == -1);
	
}

int col9_prob3_tuned_binary_search(int arr[], int t, int n)
{
	int l=-1, r = n, m;
	while(l+1 != n){
		m = (l + r) / 2;
		if(arr[m] < t) l = m;
		else r = m;
	}
	if(arr[r] == t && r != n) return r;
	return -1;
}

void col9_prob3_main()
{
	int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int ret;
	for(int i = 0 ; i < 20; ++i){
		ret = col9_prob3_tuned_binary_search(arr, i, 10);
		if(i < 10)
			assert(arr[ret] == i);
		else
			assert(ret == -1);
	}
}

int sentinel_max(int arr[], int n)
{
	int i = 0, max;
	while(i < n){
		max = arr[i];
		do{
			++i;
		}while(arr[i] <= max);
	}
	return max;
}

void col9_prob4_main()
{
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	int ret;
	ret = sentinel_max(arr, 10);
	assert(ret == 10);
}
void col9_prob5_main()
{
	cout << "Not implemented!" << endl;
}
void col9_main(int n)
{
	switch (n) {
		case 1:
			col9_prob1_main();
			break;
		case 2:
			col9_prob2_main();
			break;
		case 3:
			col9_prob3_main();
			break;
		case 4:
			col9_prob4_main();
			break;
		case 5:
			col9_prob5_main();
			break;
		default:
			cout << "No such prob number in col9..." << endl;
			break;
	}
}