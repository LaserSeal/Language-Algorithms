#include "lib.h"
#include "gramIO.h"

using namespace std;
void alg4_6(char* pathIn, char* pathOut, char* input){
	set<char*> grammer[4];
	parseGrammer(pathIn, grammer);
	
	
	cout << input << endl;	

	outputGrammer(pathOut, grammer);
}

/* Algorithm 4.6.1 - Page 126-127

input: context-free grammer G = (V, E, P, S)
	string u = x1,x2,...xn (exist in) E*

1. initialize all Xi,j to 0
2. for i = 1 to n
	for each variable A, if there is a rule A -> xi then Xi,i := Xi,i U {A}
3. for step = 2 to n
	3.1. for i = 1 ro n - step + 1
		3.1.1 for k = i to i + step - 2
			if there are variables B (exist in) Xi,k , C (exist in) Xk+1, i+step-1, and
			a rule A -> BC, then Xi,i+step-1 := Xi,i+step-1 U{A}
4. u (exist in) L(G) if S (exist in) X 1,n

*/



