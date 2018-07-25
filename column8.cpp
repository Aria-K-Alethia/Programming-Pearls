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
	COLUMN 8 ALGORITHM DESIGN TECHNIQUES

	overview:
		This column discusses common techniques related to algo design,
		including dynamic programming, divide-and-conquer, use more space
		to reduce time.
		All of them are discussed on the basis of the maximum subarray problem.

		I will implement all of the four algorithm of maximum subarray.
		Besides, two extra problems in problem set will also be implemented.

	#problem1: maximum subarray
		input: a n-dim array A.
		output:
			subarray of A which have the maximal sum. here we define output
			should be non-neg and output for array with no elem be zero.
			Therefore array with all nega elems should output zero.
		solutions:
			algo1: easiest way with O(n^3) TC.
			algo2: use dynamic programming with O(n^2) TC
			algo3: divide-and-conquer way with O(nlogn) TC
			algo4: scanning way with O(n) TC.
		comparison:
			I set n = 1000, pass = 100 and have the following outcome:
				algo1: 43.925s
				algo2: 4.806s
				algo3: 1.177s
				algo4: 0.609s
			Besides, when I set n = 10^4 the time of algo1 can not be standed
			Similarly, for algo2 n = 10^5
			for algo3 n = 10^6
			for algo4 n = 10^7( I didn't try 10^8 because of overstack).

	#problem2: find a subarray with the sum closest to t
		input: a n-dim array A, a number t.
		output:
			subarray of A whose sum is closest to t.
		solutions:
			algo1: check all possible pair, with O(n^2) TC
			algo2: when t is zero, define an extra array cursum[n]
				   let cursum[n] = cursum[n-1] + A[n],
				   if cursum[l-1] = cursum[u], we know sum of A[l...u] = 0
				   we can sort cursum and find the minimal delta.
				   so the final TC is O(nlogn)
		NOTE: I will only implement algo2
	#problem3:
		input:
			a n-dim array A,
			m triple with same form (l,u,v), each of them represents an
			operation, satisfying 0<=l<=u<n , v is a real number.
		output:
			for each triple, execute:
				for i = l up to v{
					A[i] += v
				}
			output the final array A.
		solutions:
			algo1: the most simple way with O(n^2) TC.
			algo2:
				use dynamic programming with O(n) TC.
				define a new n-dim array B.
				for each triple(l,u,v):
					B[u]   += v
					B[l-1] -= v
				representing that A[0...u] += v and A[0...l-1] -= v
				for i = n-1 down to 0{
					A[i] = A[i+1] + B[i]
				}
		NOTE: I will only implement algo2.
*/

#define COL8_PROB1_N 10000
#define COL8_PROB1_PASS 1
#define COL8_PROB2_N 10
#define COL8_PROB3_N 1000

void col8_prob1_init(int* array, int n)
{
	int base = 1000;
	//srand((unsigned int)time(NULL));
	for(int i = 0 ; i < n ; ++i){
		array[i] = rand() % 1000 - 500;
	}
}

int col8_prob1_algo1(int* array, int n)
{
	int maxsofar = 0,sum;
	for(int i = 0 ; i < n ; ++i){
		for(int j = i ; j < n ; ++j){
			sum = 0;
			for(int k = i ; k <= j ; ++k)
				sum += array[k];
			maxsofar = max(maxsofar, sum);
		}
	}
	return maxsofar;
}

int col8_prob1_algo2(int* array, int n)
{
	int maxsofar = 0,sum;
	for(int i = 0 ; i < n ; ++i){
		sum = 0;
		for(int j = i ; j < n ; ++j){
			sum += array[j];
			maxsofar = max(maxsofar, sum);
		}
	}
	return maxsofar;
}

int col8_prob1_algo3(int* array, int l, int r)
{
	//first call with 
	if(l > r) return 0; //empty array
	if(l == r) return max(array[l], 0);

	int lmax,sum,rmax,m;
	m = (l + r) / 2;
	lmax = sum = 0;
	for(int i = m ; i >= l ; --i){
		sum += array[i];
		lmax = max(lmax, sum);
	}
	rmax = sum = 0;
	for(int i = m + 1 ; i <= r ; ++i){
		sum += array[i];
		rmax = max(rmax, sum);
	}

	return public_max3(lmax + rmax, col8_prob1_algo3(array, l, m), col8_prob1_algo3(array, m+1, r));
}

int col8_prob1_algo4(int* array, int n)
{
	int maxsofar = 0, maxendhere = 0 ;
	for(int i = 0 ; i < n ; ++i){
		maxendhere = max(maxendhere + array[i], 0);
		maxsofar = max(maxsofar, maxendhere);
	}
	return maxsofar;
}

void col8_prob1_main()
{
	int n;
	int array[COL8_PROB1_N];
	cout << "col8 prob1, plz input algo number(1,2,3,4):" << endl << ">";
	cin >> n;
	srand((unsigned int)time(NULL));
	//test correctness, need not to run again
	/*
	int a,b,c,d;
	for(int i = 0 ; i < COL8_PROB1_PASS ; ++i){
		col8_prob1_init(array, COL8_PROB1_N);
		a = col8_prob1_algo1(array, COL8_PROB1_N);
		b = col8_prob1_algo2(array, COL8_PROB1_N);
		c = col8_prob1_algo3(array, 0, COL8_PROB1_N - 1);
		d = col8_prob1_algo4(array, COL8_PROB1_N);
		assert(a == b && b == c && c == d);
		cout << a << " ";
	}
	*/
	// test performance
	for(int i = 0 ; i < COL8_PROB1_PASS; ++i){
		col8_prob1_init(array, COL8_PROB1_N);
		if(n == 1) col8_prob1_algo1(array, COL8_PROB1_N);
		else if(n == 2) col8_prob1_algo2(array, COL8_PROB1_N);
		else if(n == 3) col8_prob1_algo3(array, 0, COL8_PROB1_N - 1);
		else if(n == 4) col8_prob1_algo4(array, COL8_PROB1_N);
		else cout << "col8 prob1: no such algo" << endl;
	}
}

void col8_prob2_main()
{
	//prob2, assuming t is zero, we don't consider the case when n < 2
	int array[COL8_PROB2_N] = {-5,-6,7,8,-7,-8,10,11,13,15}, cursum[COL8_PROB2_N];
	//step1, init cursum[i] = cursum[i-1] + array[i]
	cursum[0] = array[0];
	for(int i = 1 ; i < COL8_PROB2_N ; ++i)
		cursum[i] = cursum[i-1] + array[i];
	//step2, sort
	sort(cursum,cursum + COL8_PROB2_N);
	//step3, find the minimal delta, if cursum[l-1] = cursum[u] we know
	//cursum[l...u] = 0
	int delta = cursum[1] - cursum[0];
	for(int i = 2 ; i < COL8_PROB2_N ; ++i){
		delta = min(cursum[i] - cursum[i-1], delta);
	}
	cout << "col8 prob2 minimal delta: " << delta << endl;
}

typedef struct Triple
{
	int l;
	int r;
	int v;
}col8_prob3_triple;

void col8_prob3_init(col8_prob3_triple triple[], int n)
{
	// for each triple 0<=l<=r<=n-1
	int l,r;
	for(int i = 0 ; i < n ; ++i){
		l = rand()%n;
		r = rand()%n;
		triple[i].l = min(l,r);
		triple[i].r = max(l,r);
		triple[i].v = rand()%1000 - 500;
	}
}

void col8_prob3_main()
{
	col8_prob3_triple triple[COL8_PROB3_N];
	int array[COL8_PROB3_N] = {0}, cum[COL8_PROB3_N] = {0};
	int array2[COL8_PROB3_N] = {0};
	//step1, init
	srand((unsigned int)time(NULL));
	col8_prob3_init(triple,COL8_PROB3_N);
	//step2, set cum
	for(int i = 0 ; i < COL8_PROB3_N ; ++i){
		cum[triple[i].r] += triple[i].v;
		if(triple[i].l != 0) cum[triple[i].l - 1] -= triple[i].v;
		for(int j = triple[i].l ; j <= triple[i].r ; ++j){
			array2[j] += triple[i].v;
		}
	}
	//step3, let x[i] = x[i+1] + cum[i], x[n] = 0
	array[COL8_PROB3_N - 1] = cum[COL8_PROB3_N - 1];
	for(int i = COL8_PROB3_N - 2 ; i >= 0 ; --i)
		array[i] = array[i+1] + cum[i];
	//step4, check the correctness of this algo
	for(int i = 0 ; i < COL8_PROB3_N ; ++i){
		assert(array[i] == array2[i]);
	}
	cout << "col8 prob3: pass" << endl;
}

void col8_main(int n)
{
	if(n == 1) col8_prob1_main();
	else if(n == 2) col8_prob2_main();
	else if(n == 3) col8_prob3_main();
	else
		cout << "no such problem in col 8" << endl;
}