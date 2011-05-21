#include "gramIO.h"
#include "lib.h"
#include "../main/chap4.h"
#include <stdlib.h>
#include <time.h>

void removeDirectLeftRec(std::set<char*>* grammer, std::set<char*>* newGrammer, char* variable);

char* generateNewVar(std::set<char*> variables);

using namespace std;
void alg4_7(char* pathIn, char* pathOut){

	srand( time(NULL) );

	set<char*> newGrammer[4];
	set<char*> grammer[4];
	set<char*>::iterator it;

	parseGrammer(pathIn, grammer);	

	unionSet(newGrammer[ALPHABET], grammer[ALPHABET]);
	unionSet(newGrammer[VARIABLES], grammer[VARIABLES]);
	unionSet(newGrammer[START], grammer[START]);

	for( it = grammer[VARIABLES].begin(); it != grammer[VARIABLES].end(); it++){
		removeDirectLeftRec(grammer, newGrammer, *it); 
	}

	//displayGrammer(newGrammer);
	

	outputGrammer(pathOut, newGrammer);
}

/* Removal of Direct Left Recusion

Example 1:
A -> Aa | b
-----------
A -> bZ | b
A -> aZ | a

Example 2:
A -> Aa | Ab | b | c
--------------------
A -> bZ | cZ | b | c
Z -> aZ | bZ | a | b

Example 3:
A -> AB | BA | a
B -> b | c
----------------
A -> BAZ | aZ | BA | a
Z -> BZ | B
B -> b | c

A rules are broken into 2 categories:
-Left Recursive Rules:
	A -> Au1 | Au2 | ... | Auj
-The Rules
	A -> v1 | v2 | ... | vk

Which will produce these new rules
	A -> v1 | ... | vk | v1Z | ... | vkZ
	Z -> u1Z | ... | ujZ | u1 | ... | uj


*/




// Need to check if such a rule exist A -> AAAAa
void removeDirectLeftRec(set<char*>* grammer, set<char*>* newGrammer, char* variable){

	set<char*>::iterator itPro;
	char* rulePtr;
	char* newVar = generateNewVar(newGrammer[VARIABLES]);
	char* newRule;
	char* tmp;
	int size;

	insertIntoSet(newGrammer[VARIABLES], newVar);

	for( itPro = grammer[RULES].begin(); itPro != grammer[RULES].end(); ++itPro){
		if( varEqual(variable, *itPro) ){
			rulePtr = getRulePtr(*itPro);
			// If a rule is direct left recurisve
			if( (size = isVariable(rulePtr)) && (strncmp(variable, rulePtr, size)) == 0 ){	
				tmp = new char[MAX_RULE_SIZE+1];
				// Skips the inital 
				strncpy(tmp, (rulePtr+size), strnlen(rulePtr, MAX_RULE_SIZE)); 
				//tmp = newProductionRule(newVar, 		
				cout << *itPro << endl;
			} 		
		}
	}

	cout << newVar << endl;	

}


char* generateNewVar(set<char*> variables){
	
	char* newVar = new char[MAX_VAR_SIZE+1];
	char* ptr = (newVar+1);
	int random;
	strncpy(newVar, "Z\0", 2);

	while( member(variables, newVar) && strnlen(newVar, MAX_VAR_SIZE) <= MAX_VAR_SIZE){
		random = (rand() % 10);
		*(ptr++) = (char)(((int)'0')+random);
		*(ptr++) = '\0';
	}
	
	return newVar;
}
