#include "finStateIO.h"
#include "finLib.h"
#include <stdlib.h>

void convertFAtoRE(std::set<char*>* finiteState);

void makeOneFinalState(std::set<char*>* finiteState);

char* hasTransition(char* qi, char* qj, std::set<char*> transitions);

void removeTransitions(std::set<char*>* finiteState);

using namespace std;
void alg6_2(char* pathIn, char* pathOut){

	set<char*> finiteState[4];
	parseFiniteState(pathIn, finiteState);

	convertFAtoRE(finiteState);

	
	outputFiniteState(pathOut, finiteState);
	

	freeCont(finiteState[3]);
	freeCont(finiteState[2]);
	freeCont(finiteState[1]);
	freeCont(finiteState[0]);
}




void convertFAtoRE(set<char*>* finiteState){


	set<char*> removedStates;
	set<char*>::iterator i,j,k;
	char* wji, *wik, *wii, *newTran, *tmp;
	
	
	wji = EMPTY_SET;
	wik = EMPTY_SET;
	wii = EMPTY_SET;
	
	if( finiteState[FINAL].size() > 1 ){
		makeOneFinalState(finiteState);
	}	

	for( i = finiteState[STATES].begin(); i != finiteState[STATES].end(); ++i){
		if( strncmp( "q0", *i, 2) != 0 && !member(finiteState[FINAL], *i)){
			cout << *i << endl;
			for( j = finiteState[STATES].begin(); j != finiteState[STATES].end(); ++j){
				if( j != i && !member(removedStates, *j) ){
					for( k = finiteState[STATES].begin(); k != finiteState[STATES].end(); ++k){
						if( k != i && !member(removedStates, *k) ){	
							if( (wji = hasTransition(*j, *i, finiteState[TRANSITIONS])) != EMPTY_SET &&
								(wik = hasTransition(*i, *k, finiteState[TRANSITIONS])) != EMPTY_SET &&
								(wii = hasTransition(*i, *i, finiteState[TRANSITIONS])) == EMPTY_SET){
								
								
								tmp = new char[MAX_STATE_SIZE+1];	
								strncpy(tmp, wji, MAX_STATE_SIZE+1);
								strncat(tmp, wik, MAX_STATE_SIZE);

								newTran = newTransition(*j, tmp, *k);
								insertIntoSet(finiteState[TRANSITIONS], newTran);
								delete(tmp);
								delete(wji);
								delete(wik);
							
							}
							if( ((wji = hasTransition(*j, *i, finiteState[TRANSITIONS])) != EMPTY_SET &&
								(wik = hasTransition(*i, *k, finiteState[TRANSITIONS])) != EMPTY_SET) &&
								(wii = hasTransition(*i, *i, finiteState[TRANSITIONS])) != EMPTY_SET){
								
								tmp = new char[MAX_STATE_SIZE+1];	
								strncpy(tmp, wji, MAX_STATE_SIZE+1);
								strncat(tmp, wii, MAX_STATE_SIZE);
								strncat(tmp, "*", 1);
								strncat(tmp, wik, MAX_STATE_SIZE);
								
								newTran = newTransition(*j, tmp, *k);							

								insertIntoSet(finiteState[TRANSITIONS], newTran);
								delete(tmp);
								delete(wji);
								delete(wik);
								delete(wii);

							}						
							cout << "i: " << *i << " j: " << *j << " k: " << *k << endl;
						}
					}
				}
			}
			removedStates.insert(*i);
	}
	
	}	

	diffSet(finiteState[STATES], removedStates);
	removeTransitions(finiteState);
}

void makeOneFinalState(set<char*>* finiteState){
	
	set<char*>::iterator itFinal;
	char* newFinal = new char[MAX_STATE_SIZE+1];
	char* newTran;
	strncpy(newFinal, "q000", 5);	

	for( itFinal = finiteState[FINAL].begin(); itFinal != finiteState[FINAL].end(); ++itFinal){
		newTran = newTransition(*itFinal, NULL_CHAR, newFinal);	
		finiteState[TRANSITIONS].insert(newTran);
	}

	freeCont(finiteState[FINAL]);
	finiteState[FINAL].clear();
	finiteState[FINAL].insert(newFinal);
	finiteState[STATES].insert(newFinal);
}

char* hasTransition(char* qi, char* qj, set<char*> transitions){
	
	set<char*>::iterator itTran;
	vector<char*> splitTran;

	for( itTran = transitions.begin(); itTran != transitions.end(); ++itTran){
		
		splitTran = splitTransition(*itTran);

		if( strncmp( qi, splitTran[0], MAX_TRAN_SIZE) == 0 && strncmp( qj, splitTran[2], MAX_TRAN_SIZE) == 0 ){
			delete(splitTran[0]);
			delete(splitTran[2]);
			return splitTran[1];
		}
		else{
			freeCont(splitTran);
		}
	}
	
	return EMPTY_SET;	
}


void removeTransitions(set<char*>* finiteState){

	set<char*> removedTran;
	set<char*>::iterator it;
	vector<char*> splitTran;

	for( it = finiteState[TRANSITIONS].begin(); it != finiteState[TRANSITIONS].end(); ++it){
		splitTran = splitTransition(*it);
		
		if( member(finiteState[STATES], splitTran[0]) == 0 || member(finiteState[STATES], splitTran[2]) == 0 ){
			removedTran.insert(*it);
		}	
		freeCont(splitTran);
	}
	diffSet(finiteState[TRANSITIONS], removedTran);
//	freeCont(removedTran);
}
