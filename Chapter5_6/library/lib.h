//##########################################
// -Author: Brandon Schaefer
// -Created: 5/08/11
// -File Name: lib.h 
//##########################################
#include <set>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#define EMPTY_SET "0"
#define NULL_CHAR "$"

// Basic Set Functions
bool member(std::set<char*> setA, char* data);
void unionSet(std::set<char*>& setA, std::set<char*> setB);
void interSet(std::set<char*>& setA, std::set<char*> setB);
void diffSet(std::set<char*>& setA, std::set<char*> setB);
// --- End of set funcs

// Takes a production rule and takes the variable off it and 
// inserts it into the set.
char* insertVariable( std::set<char*>& variables, char* production);
void insertIntoSet(std::set<char*>& set, char* data);

bool compareSets( std::set<char*> setA, std::set<char*> setB );

// returns a pointer the rule of the production
char* getRulePtr(char* production);

// RETURNS A NEW CHAR[MAX_VAR_SIZE+1];	
char* getVariable(char* production);

// Checks if a variable is equal to one in a production rule
int varEqual(char* var, char* proVar);

// gets the length of a variable in a production rule
int variableLen( char* production );

void displayGrammer(std::set<char*>* grammer);
void displaySet(std::set<char*> setA);

bool isDigit( char digit );
bool isCapChar( char letter );
bool isLowChar( char letter );

// Both of these return 0 if no terminal or var is found
// otherwise it returns the size of the term or var in the 
// char*

int isState(char* state);

/*NULL_CHAR IS NOT A TERMINAL, NEED TO FIX THIS */
int isTerminal( char* term );
int isVariable( char* var );

// returns dynmically allocated memery. 
// d(state1, letter) = state2
char* newTransition(char* state1, char* letter, char* state2);

char* flattenSplitTransition(std::vector<char*> vecTranisition);
std::vector<char*> splitTransition(char* transition);

// Takes a set of states and converts it into a char*
char* convertSetToString(std::set<char*> setA);

// Takes a char* of states and converts it to a set.
std::set<char*> parseStateString(char* states);
