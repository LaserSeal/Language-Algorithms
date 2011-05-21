#include "finStateIO.h"
#include "lib.h"
#include <stdlib.h>

//typedef std::vector<std::vector<std::set<char*> > > setMatrix;

void alg5_7(char* pathIn, char* pathOut);
void determinEquialentStates(std::set<char*>* finiteState, char* pathOut);

bool oneIsFinal(std::set<char*> final, char* qi, char* qj);

void dist(int i, int j, int** D, setMatrix S);
bool equalTransitions(char* qi, char* qj, int** D, std::set<char*>* finiteState);
int* sameLetterTran(char* qi, char* qj, char* letter, std::set<char*> transitions);

void addToS(std::set<int*>& S, int i, int j);

int** initD(int size);
setMatrix initS(int size);

void freeSetMatrix(setMatrix S, int size);

void outputD(char* pathOut, int** D, int size);
void displayD(int** D, int size);
void displayS(setMatrix S, int size);



using namespace std;
/*int main(){

	alg5_6("dfa.txt", "dfaOut.txt");

}*/



void alg5_7(char* pathIn, char* pathOut){

	set<char*> finiteState[4];
	parseFiniteState(pathIn, finiteState);

	determinEquialentStates(finiteState, pathOut);

	freeSet(finiteState[3]);
	freeSet(finiteState[2]);
	freeSet(finiteState[1]);
	freeSet(finiteState[0]);
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


void determinEquialentStates(set<char*>* finiteState, char* pathOut){

	int stateSize = finiteState[STATES].size();
	int** D = initD(stateSize);
	int* qnm;
	setMatrix S = initS(stateSize);
		
	set<char*>::iterator qi, qj, itAlph;

	int i,j;	

	// For eery pair, first is i
	for( qi = finiteState[STATES].begin(); qi != finiteState[STATES].end(); qi++){
		i = atoi(*(qi)+1);
		// This is the j pair
		for( qj = finiteState[STATES].begin(); qj != finiteState[STATES].end(); qj++){
			j = atoi(*(qj)+1);
			// checks if i < j and if either qi or qj is an accepting state and the other is not
			if( i < j && oneIsFinal(finiteState[FINAL], *qi, *qj) ){
				D[i][j] = 1;
			}
		}	

	}	

	// 3. for every pair i,j, i < j && D[i][j] == 0
	for( qi = finiteState[STATES].begin(); qi != finiteState[STATES].end(); qi++){
		i = atoi(*(qi)+1);
		for( qj = finiteState[STATES].begin(); qj != finiteState[STATES].end(); qj++){
			j = atoi(*(qj)+1);
			if( i < j && D[i][j] == 0 ){
				// If there exist an a (exist in) E such that d(qi, a) = qm, d(qj, a) = qn and
				// D[m][n] == 1 or  D[n][m] == 1 then DIST(i,j)
				if( equalTransitions(*qi, *qj, D, finiteState) ){
					dist(i,j, D, S);	
				}
				else{	
					// Else for each a (exist in) E do: Let d(qi, a) = qm and d(qj, a) = qn
					for(itAlph = finiteState[ALPHABET].begin(); itAlph != finiteState[ALPHABET].end(); itAlph++){
						if( (qnm = sameLetterTran(*qi, *qj, *itAlph, finiteState[TRANSITIONS])) != NULL ){
							// If m < n and [i,j] != [m,n] then add [i,j] to S[m,n]
							if( qnm[0] < qnm[1] && i != qnm[0] && j != qnm[1] ){
								addToS(S[qnm[0]][qnm[1]], i, j);
							}
							// Else if m > n and [i,j] != [n,m] then add [i,j] to S[n,m]
							else if( qnm[0] > qnm[1] && i != qnm[1] && j != qnm[0]) {
								addToS(S[qnm[1]][qnm[0]], i, j);
							}
							delete(qnm);
						}
						
					}
				}

			}

		}
	}

	outputD(pathOut, D, stateSize);
	//displayD(D, stateSize);
	displayS(S, stateSize);

	for( i = 0; i < stateSize; i++){	
		delete(D[i]);
	}
	delete(D);

	freeSetMatrix(S, stateSize);
}


bool oneIsFinal(set<char*> final, char* qi, char* qj){
	if( (member(final, qi) && !member(final, qj)) || (member(final, qj) && !member(final, qi))){
		return true;
	}
	return false;
}



bool equalTransitions(char* qi, char* qj, int** D, set<char*>* finiteState){
	int* qnm;

	set<char*>::iterator itAlph, itTran;

	for( itAlph = finiteState[ALPHABET].begin(); itAlph != finiteState[ALPHABET].end(); itAlph++){
		if( (qnm = sameLetterTran(qi, qj, *itAlph, finiteState[TRANSITIONS])) != NULL){
			if(D[qnm[0]][qnm[1]] == 1 || D[qnm[1]][qnm[0]] == 1){
				delete(qnm);
				return true;
			}

			delete(qnm);
		}
	}
	return false;
}

int* sameLetterTran(char* qi, char* qj, char* letter, set<char*> transitions){

	set<char*>::iterator it;
	vector<char*> splitTran;
	
	int* qnm = new int[2];
	
	qnm[0] = -1; qnm[1] = -1;

	for( it = transitions.begin(); it != transitions.end(); it++){
		splitTran = splitTransition(*it);
		if( (strncmp(qi, splitTran[0], MAX_TRAN_SIZE) == 0)  && (strcmp(letter, splitTran[1]) == 0)) {
			qnm[0] = atoi(splitTran[2]+1);
		}
		if( (strncmp(qj, splitTran[0], MAX_TRAN_SIZE) == 0) && (strcmp(letter, splitTran[1]) == 0)) {
			qnm[1] = atoi(splitTran[2]+1);
		}
		freeVector(splitTran);
	}
	

	if( qnm[0] == -1 || qnm[1] == -1 || qnm[0] == qnm[1] ){
		delete(qnm);
		return NULL;
	}	

	return qnm;

}



void dist(int i, int j, int** D, setMatrix S){

	set<int*>::iterator it;

	D[i][j] = 1;	
	
	for( it = S[i][j].begin(); it != S[i][j].end(); it++){
		//TO DO
		dist((*it)[0], (*it)[1], D, S);
	}

}



void addToS(set<int*>& S, int i, int j){
	int* tmp = new int[2];

	tmp[0] = i;
	tmp[1] = j;

	S.insert(tmp);
}

int** initD(int size){
	
	int** D = new int*[size];

	for( int i = 0; i < size; i++){
		D[i] = new int[size];
		for( int j = 0; j < size; j++){
		//	if( i < j ){
				D[i][j] = 0;
		//	}
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
			//	S[i][j].insert(tmp);
			}
		}
	}	

	return S;


}


void outputD(char* pathOut, int** D, int size){

	char outputStream[MAX_FILE_SIZE] = "";
	char* ptr = outputStream;

	for( int i = 0; i < size; i++){
		for( int j = 0; j < size; j++){
			if( i < j){
				*(ptr++) = (char)(((int)'0')+D[i][j]);
				*(ptr++) = ' ';
			}
			else{
				*(ptr++) = '-';
				*(ptr++) = ' ';

			}
		}
		strncat(outputStream, "\n", 1);
		ptr++; 
	}
	
	*(--ptr) = '\0';

	sendStream(pathOut, outputStream);
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

	set<int*>::iterator it;

	for( int i = 0; i < size; i++){

		for( int j = 0; j < size; j++){
			if( i < j){
				for( it = S[i][j].begin(); it != S[i][j].end(); it++){
					cout << '(' << (*it)[0] << ',' << (*it)[1] << "),";
					
				}
				cout << '\t';
			}
			else{
				cout << "-\t";
			}	
		}
		cout << endl;

	}
}



void freeSetMatrix(setMatrix S, int size){

	set<int*>::iterator it;

	for( int i = 0; i < size; i++){
		for( int j = 0; j < size; j++){
			for( it = S[i][j].begin(); it != S[i][j].end(); it++){
				delete(*it);
			}
		}

	}
	


}
