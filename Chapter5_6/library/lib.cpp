
//##########################################
// -Author: Brandon Schaefer
// -Created: 5/08/11
// -File Name: lib.cpp 
//##########################################
#include "lib.h"
#include "finStateIO.h"
#include <vector>


using namespace std;

// Set Functions ------- Member, Union, Intersection, Difference
bool member(set<char*> mySet, char* data){

	set<char*>::iterator it;

	for( it = mySet.begin(); it != mySet.end(); it++){
		if( strcmp( *it, data) == 0 ){
			return 1;
		}
	}
	return 0;

}

void unionSet(set<char*>& setA, set<char*> setB){
	
	set<char*>::iterator it;
	
	for( it = setB.begin(); it != setB.end(); it++){
	//	setA.insert(*it);
		insertIntoSet(setA, *it);
	}

}


void interSet(set<char*>& setA, set<char*> setB){

	set<char*>::iterator it;
	set<char*>::iterator tmp;

	it = setA.begin();
	
	while( it != setA.end() ){
		if( !(member(setB, *it)) ){
			tmp = it;
			++it;
			setA.erase(tmp);
		}
		else{
			++it;
		}
	}
}

void diffSet(set<char*>& setA, set<char*> setB){
	
	set<char*>::iterator it;
	set<char*>::iterator tmp;

	it = setA.begin();

	while( it != setA.end()){
		if( member( setB, *it) ){
			tmp = it;
			++it;
			setA.erase(tmp);
		}
		else{
			++it;
		}
		
	}
}

// ---- End of Set Functions



// Takes a set and checks if the new data is already in the set
void insertIntoSet(std::set<char*>& set, char* data){
	
	if( !(member(set, data)) ){
		set.insert(data);
	}
	else{
		delete(data);
	}

}



void displaySet(set<char*> setA){

        set<char*>::iterator it;

        for( it = setA.begin(); it != setA.end(); it++){
                cout << *it << endl;
        }

}


bool compareSets( set<char*> setA, set<char*> setB ){

        // check size of each first, its faster that way
        if( setA.size() == setB.size()){

                set<char*>::iterator itA;
                set<char*>::iterator itB;

                for( itA = setA.begin(); itA != setA.end(); itA++){
                        if( member( setB, *itA ) == 0 ){
                                return false;
                        }
                }
                return true;
        }
        return false;
}




bool isDigit( char digit ){
	int ascii = (int)digit;
	if( ascii >= 48 && ascii <= 57 )
		return true;
	return false;
}

bool isUppChar( char letter ){
	int ascii = (int)letter;
	if( ascii >= 65 && ascii <= 90 )
		return true;
	return false;
}

bool isLowChar( char letter ){
	int ascii = (int)letter;
	if( ascii >= 97 && ascii <= 122)
		return true;
	return false;
}


int isState(char* state){
	int stateSize = 0;
	if( *state++ == 'q' || strncmp(state, EMPTY_SET, 1) == 0 ){
		stateSize++;
		while( isDigit( *state++ )){ //|| strncmp(state, EMPTY_SET, 1) == 0 ){
			stateSize++;
		}
	}

	return stateSize;
}


// return the size of the term or 0 if its false
int isTerminal(char* term){
        //checks if the first char is a letter
        int termSize = 0;
        if( isLowChar( *term ) || *term == *NULL_CHAR ){
		term++;
                termSize++;
                while( isDigit( *term++ ) ){
                        termSize++;
                }
        }
        return termSize;
}


// d(state1, letter) = state2
char* newTransition(char* state1, char* letter, char* state2){
	char* newTran = new char[MAX_TRAN_SIZE+1];
	
	strncpy(newTran, "d(\0", 3);
	strncat(newTran, state1, strlen(state1));
	strncat(newTran, ", ", 2);
	strncat(newTran, letter, strlen(letter));
	strncat(newTran, ") = ", 4);
	strncat(newTran, state2, strlen(state2));
	
	return newTran;
}


vector<char*> splitTransition(char* transition){
	
	vector<char*> vecTransition;
	char* newChar;
	int size;

	
	while( *transition != '(' && *transition ){
		transition++;
	}	



	// finds the first transition
	while( !(size = isState(transition)) && *transition ){
		transition++;		
	}


	if( size ){
		newChar = new char[size+1];
		strncpy(newChar, transition, size);
		*(newChar+size) = '\0';
		vecTransition.push_back(newChar);
		transition+=size;
	}

	// Finds the alphabet its goes too
	while( !(size = isTerminal(transition)) && *transition){
		transition++;
	}

	
	if( size ){
		newChar = new char[size+1];
		strncpy(newChar, transition, size);
		*(newChar+size) = '\0';
		vecTransition.push_back(newChar);
		transition+=size;
	}


	// Findes the state that this transitions goes too.
	while( !(size = isState(transition)) && *transition ){
		transition++;		
	}

	if( size ){
		newChar = new char[size+1];
		strncpy(newChar, transition, size);
		*(newChar+size) = '\0';
		vecTransition.push_back(newChar);
		transition+=size;
	}


	
	return vecTransition;
}

char* flattenSplitTransition(vector<char*> vecTransition){

	char* transition = new char[MAX_TRAN_SIZE+1];
	
	strncpy(transition, "d(\0", 3);

	strncat(transition, vecTransition[0], strlen(vecTransition[0]));
	strncat(transition, ", ", 2);
	strncat(transition, vecTransition[1], strlen(vecTransition[1]));
	strncat(transition, ") = ", 4);
	strncat(transition, vecTransition[2], strlen(vecTransition[2]));
	
	return transition;
}

char* convertSetToString(set<char*> setA){
	char* newString = new char[MAX_TRAN_SIZE+1];
	set<char*>::iterator it;
	*(newString) = '\0';
	
	for(it = setA.begin(); it != setA.end(); it++){
		strncat(newString, *it, strnlen(*it, MAX_STATE_SIZE));	
	}

	return newString;
}

set<char*> parseStateString(char* states){

	set<char*> setStates;
	char* newState;
	int size;
	
	while((size = isState(states))){
		newState = new char[MAX_STATE_SIZE+1];
		strncpy(newState, states, size);
		*(newState+size) = '\0';
		insertIntoSet(setStates, newState);
		states+=size;
	}	

	return setStates;
}


void freeSet(set<char*>& setA){

	set<char*>::iterator it;

	for( it = setA.begin(); it != setA.end(); ++it){
		delete(*it);
	}
}

void freeVector(vector<char*>& vec){

	vector<char*>::iterator it;

	for( it = vec.begin(); it != vec.end(); ++it){
		delete(*it);
	}
}
