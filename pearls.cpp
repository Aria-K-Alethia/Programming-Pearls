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
#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <string.h>
#include <algorithm>
#include <assert.h>
#include <set>
#include <vector>

using namespace std;

void col1_main();
void col2_main(int n);
void col4_main();
void col8_main(int n);
void col9_main(int n);
void col12_main();


int main(void)
{
	clock_t begin,end;
	begin = clock();
	//col1: col1_main();
	//col2: col2_main(2);
	//col4: col4_main();
	//col8: col8_main(3);
	col12_main();
	end = clock();
	cout << "Total time: " << (double)(end - begin)/CLOCKS_PER_SEC << "s" << endl;
    return 0;
}

int public_gcd(int i, int j)
{
	while(i != j){
		if(i < j) j -= i;
		else i -= j;
	}
	return i;
}

int public_max3(int a, int b, int c)
{
	return max(max(a, b), c);
}

/*
	COLUMN 1
	#problem1:
		input:
			a file contain n positive integers, each less than n,
			where n = 10^7, each integer will not appear twice.
		output:
			a sorted list in increasing order of the input integers.
		constraints:
			at most about 1MB can be used(here we assuming the memory
			is sufficient for storing all integer by one bit)
		pseudocode:
			1: for i=0 to n
					bit[i] = 0
			2: for i=0 to n
				read integer n
				bit[i] = 1
			3: for i=0 to n
				if bit[i] == 1
					output i
		other:
			1st: a function generate randomized array
*/

#define COL1_N 10000000
#define COL1_BITSPERBYTE 32
#define COL1_MASK 0x1F
#define COL1_SHIFT 5

void col1_generate_integers(int* array, int n)
{
	/*
		overview:
			generate integers in [0,n-1] with randomized order
		SC:
			O(n)
		TC:
			O(2*n)
	*/
	int pos,temp;
	//step1: init
	for(int i = 0 ; i < n ; ++i)
		array[i] = i;
	//step2: randomized array
	srand((unsigned int)time(NULL));
	for(int i = 0 ; i < n ; ++i){
		pos = rand()%(n - i) + i;
		temp = array[i];
		array[i] = array[pos];
		array[pos] = temp;
	}
}

void col1_bit_clr(int* bitmap, int i)
{
	bitmap[i >> COL1_SHIFT] &= (1 << ~(i & COL1_MASK));
}

void col1_bit_set(int* bitmap,int i)
{
	bitmap[i >> COL1_SHIFT] |= (1 << (i & COL1_MASK));
}

int col1_bit_test(int* bitmap, int i)
{
	return (bitmap[i >> COL1_SHIFT] & (1 << (i & COL1_MASK)));
}

void col1_set_bitmap(int* array, int* bitmap, int n)
{
	for(int i = 0 ; i < n ; ++i)
		col1_bit_set(bitmap, array[i]);
}

void col1_output(int* bitmap, int n)
{
	for(int i = 0 ; i < n ; ++i){
		if(col1_bit_test(bitmap, i))
			cout << i << endl;
	}
}

void col1_main(void)
{
	int array[COL1_N],bitmap[1 + COL1_N / COL1_BITSPERBYTE];
	//step1: generate 10^7 integers
	col1_generate_integers(array,COL1_N);
	//step2: init bit map
	memset(bitmap, 0, sizeof(int) * (1 + COL1_N / COL1_BITSPERBYTE));
	//step3: set the corresponding bit
	col1_set_bitmap(array,bitmap,COL1_N);
	//step4: output(optional)
	col1_output(bitmap,COL1_N);
	//test the time of standard sort function(optional)
	//sort(array, array + COL1_N);
}

/*
	COLUMN2 AHA! ALGORITHMS
	#problem1
		input:
			a file contains 4 billion 32-bit integers in random order.
		output:
			a 32-bit integer that doesn't appear in it.
		constraints:
			you can only use a few extra bytes, instead you can use several
			external files.
		pseudocode:
			function(pos,file){
				if(file is empty) return 
				zero,one = 0,0
				for integer in file{
					if(pos bit in integer == 1){
						++zero;
						zero_file.write(integer)
					}
					else{
						++one;
						one_file.write(integer);
					}
				}
				if(zero > one) function(pos+1,one_file);
				else function(pos+1,zero_file);
			}
	#problem2
		input:
			a n-dimensional vector, i
		output:
			a vector, which is rotated left by i positions.
			i.e. n = 4 , i = 2, abcd -> cdab
		constraints:
			TC: must be O(n)
			SC: must be less than O(n)
		model:
			this problem can be seen as a memory swap model.
		solutions:
			this problem has three solutions.
			1.juggle: a technical algorithm to rotate
			2.block swap: since swap string with equal size is easy, we use this
						  attribute to solve this problem recursively.
			3.reversal: (a^rb^r)^r = ba
		comparisions:
			in the condition of dim = 1,000,000, pass = 100, i = current_pass*10^4
			juggle: 7.889s
			swap: 7.118s
			reversal: 12.991s

	#problem3
		input:
			a dictionary of english words.
		output:
			all sets of anagrams.
		constraints:
			TC: multinomial time
		solution:
			for each class of anagram, set a unique key for indexing.
			we only need to compute the key of each word and output those
			words with same key.

*/

#define COL2_PROB2_DIM 1000000
#define COL2_PROB2_PASS 100
#define COL2_PROB2_ALGO 0

void col2_prob1_main()
{
	/*
		note this solution can also be used in the problem where you are
		requested to find duplicated elem.
	*/
	cout << "not be implemented" << endl;
}

void col2_prob2_init(int* vec)
{
	//srand((unsigned int)time(NULL));
	for(int i = 0 ; i < COL2_PROB2_DIM ; ++i){
		vec[i] = rand() % (COL2_PROB2_DIM);
	}
}

void col2_prob2_juggle(int* vec, int i)
{
	/*
		rotate vec left by i positions
		we should have gcd(i,n) loops
		TC: O(n)
		SC: O(n)
	*/
	if((i % (COL2_PROB2_DIM)) == 0) return;
	int gcd = public_gcd(COL2_PROB2_DIM, i);
	int temp,k,j;
	for(int pos = 0 ; pos < gcd ; ++pos){
		temp = vec[pos];
		j = pos;
		while(true){
			k = (j + i) % COL2_PROB2_DIM;
			if(k == pos) break;
			vec[j] = vec[k];
			j = k;
		}
		vec[j] = temp;
	}
}

void col2_prob2_swap_swap(int* vec, int a, int b, int length)
{
	/*
		exchange vec[a...a+length-1] and vec[b...b+length-1]
	*/
	int temp;
	for(int i = 0 ; i < length ; ++i){
		temp = vec[a+i];
		vec[a+i] = vec[b+i];
		vec[b+i] = temp;
	}

}

void col2_prob2_swap(int* vec, int i)
{
	/*
		this algorithm take the advantage of swapping memory of equal length
		TC: O(n)
		SC: O(n)
	*/
	if((i % (COL2_PROB2_DIM)) == 0) return;
	int a,b,p;
	a = p = i;
	b = COL2_PROB2_DIM - i;
	while(a != b){
		/*
			invariant:
				vec[0...p-a] should always in final position
				vec[p-a...p-1] should be part1
				vec[p...p+b-1] should be part2
				vec[p+b..n-1] should always in final position
			we shuold perform algo in part1 and part2
			p is the seperate point
			a is the length of part1
			b is the length of part2

			note the value of p must always be i,because we always change
			memory with equal length.
		*/
		if(a < b){
			col2_prob2_swap_swap(vec, p - a, p + b - a, a);
			b -= a;
		}
		else{
			col2_prob2_swap_swap(vec, p - a, p, b);
			a -= b;
		}
	}
	col2_prob2_swap_swap(vec, p - a, p, a);
}

void col2_prob2_reversal(int* vec, int i)
{
	/*
		reverse(0,i-1)
		reverse(i,n-1)
		reverse(0,n-1)

		TC: O(n)
		SC: O(n)
	*/

	//here we use STL algo reverse
	if((i % (COL2_PROB2_DIM)) == 0) return;
	reverse(vec,vec+i);
	reverse(vec+i,vec+COL2_PROB2_DIM);
	reverse(vec,vec+COL2_PROB2_DIM);
}

void col2_prob2_check(int* vec1,int* vec2,int shift)
{
	//check the correctness of rotation,if false output error info
	//where vec1 is original
	for(int i = 0; i < COL2_PROB2_DIM ; ++i)
		assert(vec2[i] == vec1[(i+shift)%COL2_PROB2_DIM]);
}

void col2_prob2_main()
{
	int vec[COL2_PROB2_DIM],vec2[COL2_PROB2_DIM];
	int shift;
	void (*algo[3])(int*,int) = {col2_prob2_juggle, col2_prob2_swap, col2_prob2_reversal};
	//rotate
	srand((unsigned int)time(NULL));
	for(int i = 0 ; i < COL2_PROB2_PASS ; ++i){
		col2_prob2_init(vec);
		memcpy(vec2, vec, COL2_PROB2_DIM * sizeof(int));
		shift = i*10000;
		algo[COL2_PROB2_ALGO](vec2,shift);
		col2_prob2_check(vec,vec2,shift);

		/*
		cout << shift << endl;
		for (int j = 0; j < COL2_PROB2_DIM; ++j) {
			cout << vec[j];
		}
		cout << endl;
		for (int j = 0; j < COL2_PROB2_DIM; ++j) {
			cout << vec2[j];
		}
		*/
	}

}

void col2_prob3_main()
{
	/*
		I don't implement this program cause this program is not so tricky as
		the 2nd problem.The idea in this problem is induction and key indexing

		TC: O(nllogl + nlogn) where l is the max length of word
		SC: O(nl)
	*/
	cout << "not be implemented" << endl;
}


void col2_main(int n)
{
	if     (n == 1) col2_prob1_main();
	else if(n == 2) col2_prob2_main();
	else if(n == 3) col2_prob3_main();
	else
		cout << "no such problem in col2" << endl;
}


/*
	COLUMN 4 WRITING CORRECT PROGRAMS

	overview:
		this column discuss formal verification on the basis of the binary
		search problem to help prgrammer write correct programs.
		I realize three programs in this col, including iterative binary
		search, recursive binary search and recursive power with O(logn)TC.

*/


int col4_iterative_binary_search(int* array, int n, int t)
{
	/*
		params:
			array: the array to be searched
			n: the length of array
			t: the target element
		precondition:
			array is in increasing order,
			i.e. array[i] <= array[j] for any 0<=i<j<=(n-1)
		postcondition:
			result == -1     => t doesn't present in array
			0 <= result < n  => array[result] == t
	*/
	int i=0,j=n-1,p,m;
	while(true){
		//invariant: t must in array[i...j] or not present in array
		if(i > j){
			p = -1;
			break;
		}
		m = (i + j) / 2;
		if(array[m] == t){
			p = m;
			break;
		}
		else if(array[m] < t) i = m + 1;
		else j = m - 1;
	}
	return p;
}

int col4_recursive_binary_search(int* array, int n, int t)
{
	// spec: same as col4_iterative_binary_search, but use recurrence
	// invariant: t must in array[0...n-1] or not present in original array
	int m = (n-1)/2;
	if(n == 0) return -1;
	if(array[m] == t) return m;
	else if(array[m] < t) return col4_recursive_binary_search(array + m + 1, n - m - 1, t) + m + 1;
	else return col4_recursive_binary_search(array, m , t);
}

int col4_recursive_power(int b, int p)
{
	/*
		params:
			b: base
			p: exp
		precondition:
			p >= 0
		postcondition:
			result == b^p
	*/
	int temp;
	if(p == 0) return 1;
	else if(p % 2 == 0){
		temp = col4_recursive_power(b, p / 2);
		return temp*temp;
	}
	else return b * col4_recursive_power(b, p - 1);
}

void col4_bsearch_test()
{
	int array[10] = {1,2,3,4,5,6,7,8,9,10};
	for(int i = 0 ; i < 10 ; ++i){
		assert(array[col4_iterative_binary_search(array,10,i+1)] == i+1);
		assert(array[col4_recursive_binary_search(array,10,i+1)] == i+1);
	}
	for(int i = 0 ; i < 10 ; ++i){
		assert(array[col4_iterative_binary_search(array,10,i+20)] == -1);
		assert(array[col4_recursive_binary_search(array,10,i+20)] == -1);
	}
	cout << "col4 binary search pass" << endl;
}

void col4_power_test()
{
	for(int b = 0 ; b < 10 ; ++b){
		for(int p = 0 ; p < 10 ; ++p){
			assert(col4_recursive_power(b, p) == pow(b, p));
		}
	}
	cout << "col4 power function pass" << endl;
}

void col4_main()
{
	col4_bsearch_test();
	col4_power_test();
}


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

/*
	COLUMN 12 A SAMPLE PROBLEM

	Overview:
		This column discusses about a problem, which require the programmer to select m
		distinct integer between [0, n-1] randomly. Every integer should have equal
		proability to be selected. Assume m < n. The output should be sorted.

		There are three algorithms to solve this problem
		1. from knuth(genknuth), this method is based on probability.
		2. O(mlogm) uses std::set.
		3. O(n+mlogm) generate a random permutation of n element and output the first m elements.
	PROBLEMS:
		2. biased method for the sample problem, choose i from [0,n-1] randomly, output
		   i, i+1, i+2, ..., i+m-1. This method prefer certain subsets.
		   I'd not implement this function
		4. The Coupon collector's problem. This problem indicates the time complexity of genset would
		   be O(nlogn) if m == n.
		   The Birthday paradox indicates the 50% probability to generate a repetition integer
		   if you have generated O(n**0.5) integer
		7. This problem contains two sub-problems, first is the recursive version of genknuth.
		   Second is a recursive function to generate all m-subsets of n, see genknuth_recur
		   and gen_subsets().
		8. This problem add some constraints on the sample problem
		   (1) random output order: use permutation
		   (2) allow duplication: use a bucket, sample randomly
		   (3) both (1) (2): sample directly
		9. use set and generate onlyu m random number even when m is near n.
		   This is called the floyd algorithm, see genfloyd;
		10. select a element in a set randomly, while we don't know the exact number of the
		    elements in the set until we stop reading. see random_select;
		11. Compute the probability to win a game, which equals to the probability of generating a
			random permutation of 1,2,3 in which 1 and 2 are in front of 3(The other 13 integers is
		    meanless for this problem). So the final probability is 1/3.

*/

void genknuth(int m, int n)
{
	// randomly sample m distinct integer between [0, n-1]
	srand((unsigned int)time(NULL));
	for(int i = 0 ; i < n ; ++i){
		if((rand() % (n - i)) < m){
			cout << i << endl;
			m--;
		}
	}
}

void genknuth_recur(int m, int n)
{
	if(m > 0){
		if((rand() % n) < m){
			genknuth_recur(m - 1, n - 1);
			printf("%d ", n - 1);
		}
		else{
			genknuth_recur(m, n - 1);
		}
	}
	else{
		printf("\n");
		return;
	}
}

/*
	overview:
		generate all m subsets of n, that is C(n, m)
		i.e. if m = 2, n = 4
		than the output would be:
		0 1
		0 2
		0 3
		1 2 
		1 3
		2 3
	params:
		arr: array
		length: should be m in the original call
*/
void gen_subsets(int m, int n, int arr[], int length)
{
	if(m > 0){
		// the subset would either contain n - 1 or not
		arr[m - 1] = n - 1;
		gen_subsets(m - 1, n - 1, arr, length);
		if(n > m)
			gen_subsets(m, n - 1, arr, length);
	}
	else{
		for(int i = 0 ; i < length ; ++i){
			printf("%d ", arr[i]);
		}
		printf("\n");
		return;
	}
}

void genset(int m, int n)
{
	set<int> S;
	int t;
	while(S.size() < m)
		S.insert(rand() % n);
	set<int>::iterator i;
	for(i = S.begin() ; i != S.end() ; ++i)
		cout << *i << endl;
}


void genshuf(int m, int n)
{
	int* arr = new int[n];
	for(int i = 0 ; i < n ; ++i)
		arr[i] = i;
	for(int i = 0 ; i < m ; ++i)
		myswap(arr[i], arr[i+rand()%(n - i)]);
	quick_sort2(arr, 0, m - 1);
	for(int i = 0 ; i < m ; ++i)
		cout << arr[i] << endl;
}

void genfloyd(int m, int n)
{
	set<int> S;
	set<int>::iterator i;
	for(int j = n - m ; j < n ; ++j){
		int t = rand() % (j + 1);
		if(t == j || S.find(t) == S.end())
			S.insert(t); // t not in S
		else
			S.insert(j); // t in S, j should never in S
	}
	for(i = S.begin() ; i != S.end() ; ++i)
		cout << *i << " ";
	cout << endl;
}

int random_select(vector<int> vec)
{
	srand((unsigned int)time(NULL));
	vector<int>::iterator i;
	int t = 0, n = 0;
	for(i = vec.begin() ; i != vec.end() ; ++i){
		n++;
		if((rand() % n) == (n-1))
			t = *i;
	}
	return t;
}


void col12_main()
{
	int arr[10];
	gen_subsets(3, 6, arr, 2);
	return;
}

/*
	COLUMN 13 SEARCHING
*/

/*
	COLUMN 14 HEAPS
*/

#define HEAP_PARENT(x) (x / 2)
#define HEAP_LEFT_CHILD(x) (2*x)
#define HEAP_RIGHT_CHILD(x) (2*x+1)
#define HEAP_NULL(x, n) (x < 1 || x > n)

void siftup(vector<int> heap, int n)
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

void siftdown(vector<int> heap, int n)
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