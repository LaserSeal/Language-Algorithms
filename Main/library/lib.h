#include <iostream>
#include <set>
#include <string.h>

#define NULL_CHAR "$"

bool isDigit(char);
bool isLowChar(char);
int isTerminal(char*);

void displaySet(std::set<char*>);

bool member(std::set<char*>, char*);
bool compareSets(std::set<char*> , std::set<char*> );

void insertIntoSet(std::set<char*>& setA, char* str);

void unionSet(std::set<char*>& , std::set<char*> );
void interSet(std::set<char*>& , std::set<char*> );
void diffSet(std::set<char*>& , std::set<char*> );

/*
readFile

sendStream
*/



