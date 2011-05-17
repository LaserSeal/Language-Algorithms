#include "finStateIO.h"
#include "lib.h"

typedef std::vector<std::vector<std::set<char*> > > setMatrix;

void alg5_7(char* pathIn, char* pathOut);
void determinEquialentStates(std::set<char*>* finiteState);

int** initD(int size);
setMatrix initS(int size);

void displayD(int** D, int size);
void displayS(setMatrix S, int size);


using namespace std;
/*int main(){

	alg5_6("dfa.txt", "dfaOut.txt");

}*/





void alg5_7(char* pathIn, char* pathOut){

	set<char*> finiteState[4];
	parseFiniteState(pathIn, finiteState);

	//displaySet(inputTransitionFunction("q1", "b", finiteState));
	
	//displaySet(finiteState[TRANSITIONS]);

	determinEquialentStates(finiteState);
	
	outputFiniteState(pathOut, finiteState);

/*
	freeSet(finiteState[0]);
	freeSet(finiteState[1]);
	freeSet(finiteState[2]);
	freeSet(finiteState[3]);
*/
}




/* Determination of Equivalnt States of DFA

input: DFA M = (Q, E, d, q0, F)

1. (Initialization)
	for every pair of states qi and qj, i < j
		1.1. D[i,j] := 0
		1.2. S[i,j] := EMPTY_SET
	end for
2. for every pair i,j, i < j, if one of qi or qj is an accepting state and 
	the other is not an accepting state, then set D[i,j] := 1
3. for every pair i,j, i < j, with D[i,j] = 0, do
	3.1. if there exist an a (exist in) E such that d(qi, a) = qm, d(qj, a) = qn and
		D[m,n] = 1 or D[n.m] = 1, then DIST(i,j)
	3.2. else for each a (exist in) E, do: Let d(qi, a) = qm and d(qj, a) = qn
		if m < n and [i.j] != [m,n], then add [i,j] to S[m,n]
		else if m > n and [i,j] != [n,m], then add [i,j] to S[n,m]
end for

DIST(i,j);
begin
	D[i,j] := 1
	for all [m,n] (exist in) S[i,j], DIST(m,n)
end

*/



void determinEquialentStates(set<char*>* finiteState){

	int stateSize = finiteState[STATES].size();
	int** D = initD(stateSize);
	setMatrix S = initS(stateSize);
	
	displayD(D, stateSize);


}


int** initD(int size){
	
	int** D = new int*[size];

	for( int i = 0; i < size; i++){
		D[i] = new int[size];
		for( int j = 0; j < size; j++){
			if( i < j ){
				D[i][j] = 0;
			}
		}
	
	}
	
	return D;	

}


setMatrix initS(int size){
	
	setMatrix S;
	
	S.resize(size);
	for(int i = 0; i < size; i++){
		S[i].resize(size);
		for( int j = 0; j < size; j++){
			if( i < j){
				S[i][j].insert((char*)EMPTY_SET);
			}
		}
	}	

	return S;


}

void displayD(int** D, int size){

	for( int i = 0; i < size; i++){
		for( int j = 0; j < size; j++){
			if( i < j ){
				cout << D[i][j];
			}
			else{
				cout << "-";
			}
		}
		cout << endl;
	}
}


void displayS( setMatrix S, int size){

	//TO-DO



}
