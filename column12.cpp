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