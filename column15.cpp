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
	COLUMN 15 STRINGS OF PEARLS

	Overview:
		This column's topic is String, containing three problems:
		1. counting word frequency, use (1) STL map (2) hash table
		2. longest duplicated substring, use (1) naive algo T(n) = O(n^2)
		   (2) suffix array T(n) = O(nlogn)
		3. text generation, this is trivial for me, So I didn't implement it.

*/

typedef struct HashNode
{
	char* word;
	int count;
	struct HashNode* next;
}node, *nodeptr;


#define NHASH 29989
#define MULT 31
#define MAX_WORD_LEN 100
#define MAXN 5000
nodeptr bin[NHASH];

unsigned int myhash(char* word)
{
	unsigned int ret = 0;
	char* t;
	for(t = word ; *t ; ++t)
		ret = ret * MULT + (*t);
	return ret % NHASH;
}

void incword(char* word)
{
	unsigned int h = myhash(word);
	for(nodeptr p = bin[h] ; p != NULL ; p = p->next){
		if(strcmp(p->word, word) == 0){
			(p->count)++;
			return;
		}
	}
	nodeptr p = (nodeptr)malloc(sizeof(node));
	p->count = 1;
	p->word = (char*)malloc(strlen(word) + 1);
	strcpy_s(p->word, strlen(word) + 1, word);
	p->next = bin[h];
	bin[h] = p;
}


void read_word()
{
	for (int i = 0; i < NHASH; ++i)
		bin[i] = NULL;
	char buf[MAX_WORD_LEN];
	while(scanf_s("%s", buf, MAX_WORD_LEN) != EOF){
		incword(buf);
	}
		
	for(int i = 0 ; i < NHASH; ++i){
		for(nodeptr p = bin[i]; p != NULL; p = p->next){
			cout << p->word << " " << p->count << endl;
		}
	}
}


void count_word()
{
	map<string, int> M;
	map<string, int>::iterator i;
	string t;
	while(cin >> t)
		M[t]++;
	for(i = M.begin() ; i != M.end() ; ++i)
		cout << i->first << " " << i->second << endl;
}

// longest duplicated substring

/*
	overview:
		count the common character length of p and q
	return:
		common length
*/
int comlen(char* p, char* q)
{
	int i = 0;
	while(*p && *q && (*p++ == *q++))
		++i;
	return i;
}

void longest_substring_naive(char* seq, int n, int* maxlen, int* maxi, int* maxj)
{
	int length;
	*maxlen = -1;
	for(int i = 0 ; i < n ; ++i){
		for(int j = i + 1; j < n ; ++j){
			if((length = comlen(&seq[i], &seq[j])) > (*maxlen)){
				*maxlen = length;
				*maxi = i;
				*maxj = j;
			}
		}
	}
	printf("%.*s\n", *maxlen, &seq[*maxi]);
}

int pstrcmp(const void *a, const void *b)
{
	return strcmp(*(char**)a, *(char**)b);
}

void longest_substring_suffix_array(char* seq, int n, int* maxlen, int* maxi, int* maxj)
{
	char** suffix;
	int length;
	*maxlen = -1;
	suffix = new char*[n];
	for(int i = 0 ; i < n ; ++i)
		suffix[i] = &seq[i];
	qsort(suffix, n, sizeof(char*), pstrcmp);
	for(int i = 0 ; i < n - 1 ; ++i){
		if((length = comlen(suffix[i], suffix[i+1])) > (*maxlen)){
			*maxlen = length;
			*maxi = i;
		}
	}
	printf("%.*s\n", *maxlen, suffix[*maxi]);
}


void col15_main()
{
	int maxlen, maxi, maxj;
	char word[MAXN] = "ask not what your country can do for you, but what you can do for your country";
	longest_substring_naive(word, strlen(word), &maxlen, &maxi, &maxj);
	longest_substring_suffix_array(word, strlen(word), &maxlen, &maxi, &maxj);
}