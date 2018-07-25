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