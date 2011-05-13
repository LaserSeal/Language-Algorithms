#include "finStateIO.h"
#include "lib.h"

void alg5_6(char* pathIn, char* pathOut);
void removeNonDeterminism(std::set<char*>* finiteState);
bool noArc(char* state, char* letter, std::set<char*> transitions);

std::set<char*> inputTransitionFunction(char* state, char* letter, std::set<char*>* finiteState);
std::set<char*> lambdaClosure(char* tran, std::set<char*> transitions);
std::set<char*> canReachLetter(char* letter, std::set<char*> reach, std::set<char*> transitions);

using namespace std;
int main(){

	alg5_6("dfa.txt", "dfaOut.txt");

}





void alg5_6(char* pathIn, char* pathOut){

	set<char*> finiteState[4];
	parseFiniteState(pathIn, finiteState);
	
	removeNonDeterminism(finiteState);

	vector<char*> split;
	set<char*> tmp;	

	vector<char*>::iterator itVec;

	set<char*>::iterator itState;
	set<char*>::iterator itAlph;

	//displaySet(lambdaClosure("q0", finiteState[TRANSITIONS]));
/*
	for( itState = finiteState[STATES].begin(); itState != finiteState[STATES].end(); itState++){
		for( itAlph = finiteState[ALPHABET].begin(); itAlph != finiteState[ALPHABET].end(); itAlph++){
			displaySet(inputTransitionFunction(*itState, *itAlph, finiteState));
			cout << "--" << *itAlph << endl;
		}	
		cout << "####" << *itState << endl;
	}
*/
}







void removeNonDeterminism(std::set<char*>* finiteState){

	set<char*> Q = lambdaClosure("q0", finiteState[TRANSITIONS]);
	set<char*> Y;
	set<char*>::iterator X;
	set<char*>::iterator itAlph;
	bool done = false;
	

	do{
		if( noArc(Q, finiteState) ){

		}
		else{
			done = true;
		}
		
	}while(!done);



/*
	for( X = Q.begin(); X != Q.end(); X++){
		for( itAlph = finiteState[ALPHABET].begin(); itAlph != finiteState[ALPHABET].end(); itAlph++){
			if( noArc(*X, *itAlph, finiteState[TRANSITIONS])){
				cout << *X << " | " << *itAlph << endl;
				Y = inputTransitionFunction(*X, *itAlph, finiteState);
				displaySet(Y);
			}

			
		}
	}
*/


}


// Returns true if there is no arc for state to letter
bool noArc(set<char*> states,  set<char*>* finiteState){
	
	vector<char*> splitTran;
	set<char*>::iterator itTran;

	for( itTran = transitions.begin(); itTran != transitions.end(); itTran++){
		splitTran = splitTransition(*itTran);
		if( strcmp( state, splitTran[0]) == 0 && strcmp(letter, splitTran[1]) == 0){
			return false;	
		}
	}
	return true;
}


// ###################### Input Transition Function ##################################
/*

t(qi, a) = U lambdaClosure(d(qj,a)), qj (exist in) lambdaClosure(qi)

*/
set<char*> inputTransitionFunction(char* state, char* letter, set<char*>* finiteState){

	vector<char*> splitTran;
	set<char*> lambdaSet;
	set<char*> reachable;
	set<char*>::iterator itState;
		
	
	lambdaSet = lambdaClosure(state, finiteState[TRANSITIONS]);
		
	unionSet(reachable, canReachLetter(letter, lambdaSet, finiteState[TRANSITIONS]));
	
	return reachable;
}

// What qi can reach with out processing any chars
// Lambda Closure
set<char*> lambdaClosure(char* state, set<char*> transitions){
	
	vector<char*> splitTran;
	set<char*>::iterator itTran;	
	set<char*> reachable;
	char* newState;
	int size;
	
	reachable.insert(state);

	for( itTran = transitions.begin(); itTran != transitions.end(); itTran++){
		splitTran = splitTransition(*itTran);
		if( strcmp(splitTran[1], NULL_CHAR) == 0 && strcmp(state, splitTran[0]) == 0){
			unionSet(reachable, lambdaClosure(splitTran[2], transitions));
		}
	}
	
	return reachable;
}

set<char*> canReachLetter(char* letter, set<char*> lambdaSet, set<char*> transitions){
	
	vector<char*> splitTran;
	set<char*> reachable;
	set<char*>::iterator itTran;
	set<char*>::iterator itReach;
	char* newState;
	int size;

	for( itReach = lambdaSet.begin(); itReach != lambdaSet.end(); itReach++){
		for( itTran = transitions.begin(); itTran != transitions.end(); itTran++){
			splitTran = splitTransition(*itTran);
			
			// U lambdaClosure(d(state, letter)), state (exist in) lambdaClosure of qi
			if(strcmp(*itReach, splitTran[0]) == 0 && strcmp(letter, splitTran[1]) == 0){
				unionSet(reachable, lambdaClosure(splitTran[2], transitions));
			}
		}		
	}
	
	return reachable;
}

