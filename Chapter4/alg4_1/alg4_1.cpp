#include "gramIO.h"
#include "gramLib.h"
#include "lib.h"
#include "../main/chap4.h"



void rmRecursiveStart(std::set<char*>* grammer);
void changeGrammer(std::set<char*>* grammer);
char* generateNewStart(std::set<char*>* grammer);
bool hasStart(char* rule, char* start);

using namespace std;
/*int main(){
	alg4_1("grammer.txt", "newGrammer.txt");
}*/

void alg4_1(char* pathIn, char* pathOut){
	
	set<char*> grammer[4];
	parseGrammer(pathIn, grammer);
	rmRecursiveStart(grammer);	
	outputGrammer(pathOut, grammer);
}

void rmRecursiveStart( set<char*>* grammer){

	set<char*>::iterator itPro;
	char* start = *(grammer[START].begin());
	int startSize = strlen(start);

		
	for( itPro = grammer[RULES].begin(); itPro != grammer[RULES].end(); itPro++){	
		if( varEqual( start, *itPro) ){
			if( hasStart( getRulePtr( *itPro ), start )) {
				// add new start state
				changeGrammer(grammer);
				return;
			}			
		}
	}

}

// Things to change:
// First produce a new uniqe start symbol: S U (0)* EX: S0 or S00 etc...
// Make new rule newStart -> oldStart (S' -> S)
// Change the start symbol in grammer[START]
void changeGrammer(set<char*>* grammer){

	char* oldStart = *(grammer[START].begin());
	char* newStart = generateNewStart(grammer);
	char* startRule = new char[MAX_RULE_SIZE+1];
	
	strncpy(startRule, newStart, MAX_VAR_SIZE);
	strncat(startRule, " ", 1);
	strncat(startRule, oldStart, MAX_VAR_SIZE);

	grammer[RULES].insert(startRule);
	
	grammer[VARIABLES].insert(newStart);

	grammer[START].clear();
	grammer[START].insert(newStart);	


}
// RETURNS A PTR TO THE NEW START
char* generateNewStart( set<char*>*grammer){
	char* newStart = new char[MAX_VAR_SIZE+1];
	char* oldStart = *(grammer[START].begin());
	int startLen = strlen(oldStart);

	strncpy( newStart, oldStart, startLen);
	*(newStart+startLen) = '\0';	
	// Need to check if at any point im trying to copy past MAX_VAR_SIZE
	while( member(grammer[VARIABLES], newStart) ){
		strncat(newStart, "0\0", 2);
	}
	return newStart;
}

// Checks if given a rule if the start symbol exsit in it
bool hasStart(char* rule, char* start){
	
	int size;

	while(*rule){
		if( (size = isVariable(rule))){
			if( strncmp(start, rule, size) == 0){
				return true;
			}
			rule += size;
		}
		else{
			rule++;
		}
	}
	return false;
}



