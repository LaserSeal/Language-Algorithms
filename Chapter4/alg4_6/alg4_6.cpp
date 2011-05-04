#include "lib.h"
#include "gramIO.h"

char** CYKalg(std::set<char*>* grammer, const char* input); 

using namespace std;
void alg4_6(char* pathIn, char* pathOut, const char* input){
	set<char*> grammer[4];
	parseGrammer(pathIn, grammer);
	
	CYKalg(grammer, input);

	outputGrammer(pathOut, grammer);
}

/*
Basic Description
Step 1: For each substring xi,i of u with length one, find the set Xi,i of all variables A with a rule A -> xi,i
Step 2: for each sub string xi,i+1 of u with length two find the set Xi,i+1 of all variables that initain derivations A =*> xi,i+1
Step 3: for each sub string xi,i+2 of u with length two find the set Xi,i+2 of all variables that initain derivations A =*> xi,i+2


Algorithm 4.6.1 - Page 126-127

input: context-free grammer G = (V, E, P, S)
	string u = x1,x2,...xn (exist in) E*

1. initialize all Xi,j to {}
2. for i = 1 to n
	for each variable A, if there is a rule A -> xi then Xi,i := Xi,i U {A}
3. for step = 2 to n
	3.1. for i = 1 ro n - step + 1
		3.1.1 for k = i to i + step - 2
			if there are variables B (exist in) Xi,k , C (exist in) Xk+1, i+step-1, and
			a rule A -> BC, then Xi,i+step-1 := Xi,i+step-1 U{A}
4. u (exist in) L(G) if S (exist in) X 1,n

*/

// RETURNS A CHAR** FREE ME
char** CYKalg(set<char*>* grammer, const char* input){
	
	int n = strlen(input);
	char** X = new char*[n];
	
	for( int i = 0; i < n; i++)
		X[i] = new char[n];

	displayGrammer(grammer);

	
	cout << input << endl;


	return NULL;
}
