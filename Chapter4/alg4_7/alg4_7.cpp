#include "gramIO.h"
#include "gramLib.h"
#include "lib.h"
#include "../main/chap4.h"
#include <stdlib.h>
#include <time.h>

void removeDirectLeftRec(std::set<char*>* grammer, std::set<char*>* newGrammer, char* variable);

bool isDLR(std::set<char*>* grammer, char* var);

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
	

	outputGrammer(pathOut, newGrammer);

	freeCont(grammer[3]);
	freeCont(grammer[2]);
	freeCont(grammer[1]);
	freeCont(grammer[0]);
//	freeCont(newGrammer[3]);
	freeCont(newGrammer[2]);
//	freeCont(newGrammer[1]);
//	freeCont(newGrammer[0]);

}

// This function is for GNF, since it has
// to check if any of the new rules have DLR
// This way I can modifiy the grammer on the fly
void alg4_7_GNF(set<char*>* grammer, char* var){
	set<char*> newGrammer[4];
	set<char*>::iterator it, tmp;	

	unionSet(newGrammer[VARIABLES], grammer[VARIABLES]);

	removeDirectLeftRec(grammer, newGrammer, var);

	for( it = grammer[RULES].begin(); it != grammer[RULES].end(); ){
		if( varEqual( var, *it ) ){
			tmp = it;
			++it;
			grammer[RULES].erase(tmp);
		}
		else{
			++it;
		}
	}

	unionSet(grammer[RULES], newGrammer[RULES]);
	unionSet(grammer[VARIABLES], newGrammer[VARIABLES]);

	displaySet(grammer[RULES]);

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
	int oldRuleSize = newGrammer[RULES].size();
	int size;

	if( isDLR(grammer, variable) ){
		insertIntoSet(newGrammer[VARIABLES], newVar);
	
		for( itPro = grammer[RULES].begin(); itPro != grammer[RULES].end(); ++itPro){
			if( varEqual(variable, *itPro) ){
				rulePtr = getRulePtr(*itPro);
				// If a rule is direct left recurisve
				if( (size = isVariable(rulePtr)) && (strncmp(variable, rulePtr, size)) == 0 ){		
					// First one for Z -> u1 | ... | uj
					tmp = new char[MAX_RULE_SIZE+1];
					// rulePtr+size skips the recusive variable 
					strncpy(tmp, (rulePtr+size), strnlen(rulePtr, MAX_RULE_SIZE)); 
					newRule = newProduction(newVar, tmp);
					
					delete(tmp);

					// Now need to make new memory for the Z -> Au1 | ... | Auj
					tmp = new char[MAX_RULE_SIZE+1];
					strncpy(tmp, newRule, MAX_RULE_SIZE);
					
					// Insert the u1 | ... | uj rule, since this can delete the pointer
					// we need to make sure we copy it into a tmp first 
					insertIntoSet(newGrammer[RULES], newRule);  
				
					// Now add the newVar on to u1 | ... | uj such that Z -> u1Z | ... | ujZ	
					strncat(tmp, newVar, MAX_VAR_SIZE);	
						
					//Puts the new rule into the RULES, it will take care of
					//the delete if it is already in RULES	
					insertIntoSet(newGrammer[RULES], tmp);
				} 
				// It is a non-DLR rule
				else{
					newRule = new char[MAX_RULE_SIZE+1];		
					strncpy(newRule, *itPro, MAX_RULE_SIZE+1);
					
					tmp = new char[MAX_RULE_SIZE+1];
					strncpy(tmp, newRule, MAX_RULE_SIZE+1);
					strncat(tmp, newVar, MAX_VAR_SIZE);
		

					insertIntoSet(newGrammer[RULES], newRule);
					insertIntoSet(newGrammer[RULES], tmp);
				}
			}

		}

	}
	else{
		for( itPro = grammer[RULES].begin(); itPro != grammer[RULES].end(); ++itPro){
			if( varEqual(variable, *itPro) ){
				newRule = new char[MAX_RULE_SIZE+1];
				strncpy(newRule, *itPro, MAX_RULE_SIZE+1);
				insertIntoSet(newGrammer[RULES], newRule);
			}	
		}
	}

}
// Use this to tell if a grammer is DLR 
bool isDLR(set<char*>* grammer, char* var){

	set<char*>::iterator it;
	char* rulePtr;
	int size;
	
	for( it = grammer[RULES].begin(); it != grammer[RULES].end(); ++it){
		rulePtr = getRulePtr(*it);
		if( varEqual(var, *it) ){
			if( (size = isVariable(rulePtr)) && strncmp(var, rulePtr, size) == 0) {
				return true;
			}
		}

	}

	return false;
	
}


char* generateNewVar(set<char*> variables){
	
	char* newVar = new char[MAX_VAR_SIZE+1];
	char* ptr = (newVar+1);
	int random;
	strncpy(newVar, "Z\0", 2);

	while( member(variables, newVar) && strnlen(newVar, MAX_VAR_SIZE) <= MAX_VAR_SIZE){
		random = (rand() % 10);
		*(ptr++) = (char)(((int)'0')+random);
		*(ptr) = '\0';
	}
	
	return newVar;
}
