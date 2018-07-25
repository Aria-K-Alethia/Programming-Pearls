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