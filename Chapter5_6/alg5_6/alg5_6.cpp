#include "finStateIO.h"
#include "lib.h"

void alg5_6(char* pathIn, char* pathOut);
void removeNonDeterminism(std::set<char*>* finiteState);
void finalStates(std::set<char*> Q, std::set<char*>* finiteState);
char* getY(char* letter, std::set<char*> statesX, std::set<char*>* finiteState);
char* makeNewTransition(char* state, char* letter, char* state2);
bool noArc(std::set<char*> states, std::set<char*> alphabet, std::set<char*> transitions);
bool transitionExist(char* state, char* letter, std::set<char*> transitions);

std::set<char*> inputTransitionFunction(char* state, char* letter, std::set<char*>* finiteState);
std::set<char*> lambdaClosure(char* tran, std::set<char*> transitions);
std::set<char*> canReachLetter(char* letter, std::set<char*> reach, std::set<char*> transitions);

using namespace std;
/*int main(){

	alg5_6("dfa.txt", "dfaOut.txt");

}*/





void alg5_6(char* pathIn, char* pathOut){

	set<char*> finiteState[4];
	parseFiniteState(pathIn, finiteState);

	//displaySet(inputTransitionFunction("q1", "b", finiteState));
	
//	displaySet(finiteState[TRANSITIONS]);

	
	removeNonDeterminism(finiteState);

	outputFiniteState(pathOut, finiteState);


	freeSet(finiteState[0]);
	freeSet(finiteState[1]);
	freeSet(finiteState[2]);
	freeSet(finiteState[3]);
}




/* Construction of DM, a DFA Equivalent to NFA-Lambda M

input: an NFA-Lambda M = {Q, E, d, q0, F}

1. init Q' to lambda-closure(q0)
2. repeat
	2.1. IF there is a noda X (exist in) Q' and a symbol a (exist in) E with no arc
		leaving X labeled a, THEN
		2.1.1. let Y = U inputTransitionFunction(qi, a) where qi (exist in) X
		2.1.2. IF Y (does not exist in) Q', then set Q' := Q' U{Y}
		2.1.3. add an arc from X to Y labeled a
	else done := true
until done


*/


void removeNonDeterminism(std::set<char*>* finiteState){

	set<char*> Q = lambdaClosure((char*)"q0", finiteState[TRANSITIONS]);
	set<char*> tmpSet;
	set<char*> statesX;
	set<char*>::iterator X = Q.begin();
	set<char*>::iterator itAlph;
	char* Y;
	char* newTran;
	bool done = false;



	do{
		if( noArc(Q, finiteState[ALPHABET], tmpSet) && X != Q.end()){
			statesX = parseStateString(*X);
			for(itAlph = finiteState[ALPHABET].begin(); itAlph != finiteState[ALPHABET].end(); itAlph++){
				Y = getY(*itAlph, statesX, finiteState);
				newTran  = makeNewTransition(*X, *itAlph, Y);
				insertIntoSet(Q, Y);
				insertIntoSet(tmpSet, newTran);
			}
			freeSet(statesX);
			++X;	
		}
		else{
			done = true;
		}
		
	}while(!done);

	freeSet(finiteState[TRANSITIONS]);
	finiteState[TRANSITIONS].clear();
	unionSet(finiteState[TRANSITIONS], tmpSet);

	finalStates(Q, finiteState);
}

void finalStates(set<char*> Q, set<char*>* finiteState){

	set<char*> newFinalStates;
	set<char*> splitState;
	set<char*>::iterator itState;
	set<char*>::iterator it;

	for( itState = Q.begin(); itState != Q.end(); itState++){
		splitState = parseStateString(*itState);
		for( it = splitState.begin(); it != splitState.end(); it++){
			if( member( finiteState[FINAL], *it ) ){
				insertIntoSet(newFinalStates, *itState);
			}
		}
		freeSet(splitState);
	}

	freeSet(finiteState[FINAL]);
	finiteState[FINAL].clear();
	unionSet(finiteState[FINAL], newFinalStates);
}



char* makeNewTransition(char* state1, char* letter, char* state2){

	char* newTran = new char[MAX_TRAN_SIZE+1];

	if( *state2){
		newTran = newTransition(state1, letter, state2);
	}
	else{
		if(*state1){	
			newTran = newTransition(state1, letter, (char*)EMPTY_SET);
		}
		else{
			newTran = newTransition((char*)EMPTY_SET, letter, (char*)EMPTY_SET);	
		}
	}

	return newTran;
}

char* getY( char* letter, set<char*> statesX, set<char*>* finiteState){

	set<char*> Y;
	char* strY;
	set<char*>::iterator itState;


	for( itState = statesX.begin(); itState != statesX.end(); itState++){
		unionSet(Y, inputTransitionFunction(*itState, letter, finiteState));
	}	
	strY = convertSetToString(Y);
	freeSet(Y);
	return strY;
}
// Returns true if it is not a DFA yet, hence that there is a state
// that does not have an arc for all the alphabet letters
bool noArc(set<char*> states,  set<char*> alphabet, set<char*> transitions){
	
	set<char*>::iterator itState;
	set<char*>::iterator itAlph;

	for( itState = states.begin(); itState != states.end(); itState++){
		for( itAlph = alphabet.begin(); itAlph != alphabet.end(); itAlph++){
			if(!transitionExist(*itState, *itAlph, transitions)){
				return true;
			}
		}
	}
	return false;
}

// Finds a trasition for the given state a letter, if none exist return false
bool transitionExist(char* state, char* letter, set<char*> transitions){
	vector<char*> splitTran;
	set<char*>::iterator itTran;
	

	for( itTran = transitions.begin(); itTran != transitions.end(); itTran++){
		splitTran = splitTransition(*itTran);
		if( strcmp(state, splitTran[0]) == 0 && strcmp(letter, splitTran[1]) == 0){
			return true;
		}	

		delete splitTran[2];
		delete splitTran[1];
		delete splitTran[0];
			
	}

	return false;


}
// ###################### Input Transition Function ##################################
/*

t(qi, a) = U lambdaClosure(d(qj,a)), qj (exist in) lambdaClosure(qi)

*/
set<char*> inputTransitionFunction(char* state, char* letter, set<char*>* finiteState){

	set<char*> lambdaSet;
	set<char*> reachable;
	set<char*>::iterator itState;
		
	
	lambdaSet = lambdaClosure(state, finiteState[TRANSITIONS]);
		
	unionSet(reachable, canReachLetter(letter, lambdaSet, finiteState[TRANSITIONS]));

	freeSet(lambdaSet);	

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

	newState = new char[MAX_STATE_SIZE+1];
	strncpy(newState, state, MAX_STATE_SIZE);
	insertIntoSet(reachable, newState);

	for( itTran = transitions.begin(); itTran != transitions.end(); itTran++){
		splitTran = splitTransition(*itTran);
		if( strcmp(splitTran[1], NULL_CHAR) == 0 && strcmp(state, splitTran[0]) == 0){
			unionSet(reachable, lambdaClosure(splitTran[2], transitions));
		}
		//cout << splitTran[0] << ", " << splitTran[1] << " = " << splitTran[2] << endl;
		delete splitTran[0];
		delete splitTran[1];
		delete splitTran[2];
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
			delete splitTran[0];
			delete splitTran[1];
			delete splitTran[2];
		}		
	}
	
	return reachable;
}

