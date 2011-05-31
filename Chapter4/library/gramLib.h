//##########################################
// -Author: Brandon Schaefer
// -Created: 5/08/11
// -File Name: gramLib.h 
//##########################################
#include <set>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

// Used in alg4_6
typedef std::vector<std::vector<std::set<char*> > > setMatrix;

#define NULL_CHAR "$"

/*
#ifndef __LIB_H
#define __LIB_H

// Basic Set Functions
bool member(std::set<char*> setA, char* data);
void unionSet(std::set<char*>& setA, std::set<char*> setB);
void interSet(std::set<char*>& setA, std::set<char*> setB);
void diffSet(std::set<char*>& setA, std::set<char*> setB);
// --- End of set funcs

void insertIntoSet(std::set<char*>& set, char* data);

bool compareSets( std::set<char*> setA, std::set<char*> setB );

void displaySet(std::set<char*> setA);

bool isDigit( char digit );
bool isCapChar( char letter );
bool isLowChar( char letter );

// Both of these return 0 if no terminal or var is found
// otherwise it returns the size of the term or var in the 
// char*

NULL_CHAR IS NOT A TERMINAL, NEED TO FIX THIS 
int isTerminal( char* term );


*/


int isVariable( char* var );


char* newProduction(char* variable, char* rule);

// Takes a production rule and takes the variable off it and 
// inserts it into the set.
char* insertVariable( std::set<char*>& variables, char* production);

// returns a pointer the rule of the production
char* getRulePtr(char* production);

// RETURNS A NEW CHAR[MAX_VAR_SIZE+1];	
char* getVariable(char* production);

// Checks if a variable is equal to one in a production rule
int varEqual(char* var, char* proVar);

// gets the length of a variable in a production rule
int variableLen( char* production );

void displayGrammer(std::set<char*>* grammer);




//************************************************************
/* bug :: SKIPPING THE NULL_CHAR, NEED TO PUT NULL_CHAR INTO THE VECTOR */
//************************************************************
// Splits a rule up by terminals and varibles
// and puts it into a vector
std::vector<char*> splitProduction(char* production);
char* flattenProductVector(std::vector<char*> splitRule);

#ifndef __FREE_H
#define __FREE_H

template <class T>
inline void freeCont(T& cont){
	typename T::iterator it;

	for( it = cont.begin(); it != cont.end(); it++){
		delete(*it);
	}
}

#endif


void freeGrammer(std::set<char*>* grammer);
