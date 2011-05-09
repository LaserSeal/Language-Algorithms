
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
		setA.insert(*it);
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
	if( *state++ == 'q' ){
		stateSize++;
		while( isDigit( *state++ ) ){
			stateSize++;
		}
	}

	return stateSize;
}


// return the size of the term or 0 if its false
int isTerminal(char* term){
        //checks if the first char is a letter
        int termSize = 0;
        if( isLowChar( *term++ ) ){
                termSize++;
                while( isDigit( *term++ ) ){
                        termSize++;
                }
        }
        return termSize;
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


