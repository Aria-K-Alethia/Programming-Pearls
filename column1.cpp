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