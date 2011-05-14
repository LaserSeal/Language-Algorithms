#include "lib.h"
#include "gramIO.h"
#include "latex.h"

#define MAX_NUM_VAR 8

void CYKalg(std::set<char*>* grammer, char* input, char* pathOut); 
void addDerivableVars( std::set<char*> B, std::set<char*> C, std::set<char*>& addTo, std::set<char*> rules);
std::vector<std::vector<std::set<char*> > > init2DMatrix(int n);


void outputMatrix(std::vector<std::vector<std::set<char*> > > X, char* pathOut, int size);
int maxSetSize(std::vector<std::vector<std::set<char*> > > X, int n);
void printDiagMatrix( std::vector<std::vector<std::set<char*> > >, int n);



using namespace std;
void alg4_6(char* pathIn, char* pathOut, char* input){
	set<char*> grammer[4];
	parseGrammer(pathIn, grammer);

	CYKalg(grammer, input, pathOut);
}

/*
Algorithm 4.6.1 - Page 126-127

input: context-free grammer G = (V, E, P, S)
	string u = x1,x2,...xn (exist in) E*

1. initialize all Xi,j to {}
2. for i = 1 to n
	for each variable A, if there is a rule A -> xi then Xi,i := Xi,i U {A}
3. for step = 2 to n
	3.1. for i = 1 to n - step + 1
		3.1.1 for k = i to i + step - 2
			if there are variables B (exist in) Xi,k , C (exist in) Xk+1, i+step-1, and
			a rule A -> BC, then Xi,i+step-1 := Xi,i+step-1 U{A}
4. u (exist in) L(G) if S (exist in) X 1,n

*/

void CYKalg(set<char*>* grammer, char* input, char* pathOut){

	vector<char*> splitInput = splitProduction(input);// splitProduction(input);	
	set<char*>::iterator itPro;	
	char* var;
	int n = splitInput.size();

	// 1. initialize all Xi,j to {}
	vector<vector<set<char*> > > X = init2DMatrix(n);

	// 2. for i = 1 to n
	// 	for each variable A, if there is a rule A -> xi then Xi,i := Xi,i U {A}
	for(int i = 1; i <= n; i++){
		for( itPro = grammer[RULES].begin(); itPro != grammer[RULES].end(); itPro++){
			if( strncmp( getRulePtr(*itPro), splitInput[i-1], MAX_RULE_SIZE) == 0 ){
				X[i][i].insert( getVariable(*itPro));				
			}
		}
	}

	//3.
	for( int step = 2; step <= n; step++){
		for( int i = 1; i <= (n - step + 1); i++){
			for( int k = i; k <= (i + step - 2 ); k++){
				addDerivableVars(X[i][k], X[k+1][i+step-1], X[i][i+step-1], grammer[RULES]);		
			}
		}

	}

	//4.
	if( member(X[1][n], *(grammer[START].begin()))){
		cout << input << ": is in the language" << endl;
	}

	//printDiagMatrix(X, n);
	outputLatex(X, pathOut, n);
//	outputMatrix(X, pathOut, n);
}


// if A -> BC, returns the variable that was 
void addDerivableVars( set<char*> B, set<char*> C, set<char*>& addTo, set<char*> rules){
	
	set<char*>::iterator itPro;
	set<char*>::iterator itB;
	set<char*>::iterator itC;
	char* var;
	char* rule, *rulePtr;
	int size = 0;

	if( B.size() <= 0 && C.size() <= 0 ){
		return;
	}

	for( itPro = rules.begin(); itPro != rules.end(); itPro++){
		rule = getRulePtr(*itPro);
		rulePtr = rule;
		for( itB = B.begin(); itB != B.end(); itB++){
			for( itC = C.begin(); itC != C.end(); itC++){
			
				if( (size = isVariable(rulePtr)) && strncmp(rulePtr, *itB, size) == 0){
					rulePtr+=size;
				}
	
				if( (size = isVariable(rulePtr)) && strncmp(rulePtr, *itC, size) == 0){
					rulePtr+=size;
				}

				if( !(*rulePtr) ){
					var = getVariable(*itPro);
					insertIntoSet(addTo, var);
				}	
				rulePtr = rule;
			}	
		}
	}
}

vector<vector<set<char*> > > init2DMatrix(int n){

	vector<vector<set<char*> > > X;

	X.resize(n+1);
	for( int i = 1; i <= n; i++){
		X[i].resize(n+1);
	}
	
	return X;
}



// *** Looking pretty functions *** \\\

void outputMatrix(vector<vector<set<char*> > > X, char* pathOut, int n){

	set<char*>::iterator it;
	char outputStream[MAX_FILE_SIZE*2] = "";

	for( int i = 1; i <= n; i++){
		for( int j = 1; j <= n; j++){
			if( j < i ){
				strncat(outputStream, "-\t\t\t", 4);
			}
			else{
				strncat(outputStream, "{", 1);	
				for(it = X[i][j].begin(); it != X[i][j].end();){	
				 	strncat(outputStream, *it, MAX_VAR_SIZE);
					if( (++it) != (X[i][j].end()))
						strncat(outputStream, ",", 1);
				}
				strncat(outputStream, "}\t\t\t", 4);
			}
		}
		strncat(outputStream, "\n", 1);
	}

	sendStream(pathOut, outputStream);
}



int maxSetSize(vector<vector<set<char*> > > X, int n){

	int tmpSize, maxSize = 0;

	for( int i = 1; i <= n; i++){
		for( int j = 1; j <= n; j++){
			tmpSize = X[i][j].size();
			if( tmpSize > maxSize){
				maxSize = tmpSize;
			}	
		}
	}

	return maxSize;
}


void printDiagMatrix( vector<vector<set<char*> > > X, int n){


	set<char*>::iterator it;
	int numTab = (maxSetSize(X, n) * MAX_VAR_SIZE)/5;

	cout << numTab << "--" << endl;

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if( j < i ){
				cout << "-\t";	
			}
			else{
				cout << "{";
				for(it = X[i][j].begin(); it != X[i][j].end();){	
				 	cout << *it;
					if( (++it) != (X[i][j].end())){
						cout << ",";
					}
				}
				cout << "}\t";
			}

		}
		cout << endl;
	}
}
