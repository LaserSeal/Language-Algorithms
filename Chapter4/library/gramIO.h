
//##########################################
// -Author: Brandon Schaefer
// -Created: 5/14/11
// -File Name: gramIO.h
//##########################################


#include <set>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>



//##############################
// Reading in File Functions 
//##############################

#define MAX_FILE_SIZE 512

// Uses readFile to get a dynamic array with the
// exact size of the file in a char*
char* readGrammer(char* path);

// If you dont want a dynamic array with the exact 
// size of the file use readFile(...); 
int readFile(char* path, char* file);

void freeFile(char* file);


//##############################
// End of Reading in a file 
//##############################

//##############################
// Parsing Grammer Functions
//##############################
// This uses the reading in file so the user wont have to worry about mem leaks
// its gets handled, all they have to provide is a set<char*> grammer[3].

#define VARIABLES 0
#define ALPHABET  1
#define RULES     2
#define START	  3

#define MAX_VAR_SIZE 8
#define MAX_TERM_SIZE 8
#define MAX_RULE_SIZE 32

//----
void parseGrammer(char* path, std::set<char*>* grammer);
void parseLine(std::set<char*>* grammer, char* line);

// gets the variable and also returns a pointer to the var
char* getVariable(std::set<char*>& variables, char* line);

// Goes through the line and finds terminals and adds those to
// the alphabet
void getAlphabet(std::set<char*>& alphabet, char* line);
//int isTerminal(char* term);

// Gets the rules from the line and the var found
void getRules(std::set<char*>& rules, char* line, char* var);

//##############################
// End of Parsing Functions 
//##############################


//##############################
// Start of Outputing Grammer
//##############################

// Takes a file, and a grammer you used when reading in a grammer
void outputGrammer( char* file, std::set<char*>* grammer);

// Adds the start symbol first
void insertStart( std::set<char*>* grammer, char* outputStream );

// Used when re-constructing the grammer into a format that it was read in
void insertRules( char* var,  std::set<char*> rules, char* outputStream);

// Used to send the outputStream made in outputGrammer
void sendStream( char* path, char* outputStream );


//##############################
// End of Outputing Grammer
//##############################
