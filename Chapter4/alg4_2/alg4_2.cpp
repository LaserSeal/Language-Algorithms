
#include <math.h>
#include <stdio.h>
#include "lib.h"
#include "gramIO.h"
#include "../main/chap4.h"


std::set<char*> initNullSet( std::set<char*>* grammer );
std::set<char*> buildNullSet( std::set<char*>* grammer);
bool ruleInPrev( char* rule, std::set<char*> prevSet );

void removeNullRules( std::set<char*> nullSet, std::set<char*>* grammer);
//int variablePos( char* rule );
int getNullAmount( char* rule, std::set<char*> nullSet);

char* getPermutationList( int nullAmount, char* rule);

void addNewRules(char* rule, std::set<char*> nullSet, std::set<char*>& rules);

void removeOldNullRules(std::set<char*>& rules, char* start);
//bool compareSets( std::set<char*> setA, std::set<char*> setB);


using namespace std;
/*int main(){
	alg4_2("grammer.txt", "newGrammer.txt");
}*/

void alg4_2(char* pathIn, char* pathOut){	
	set<char*> grammer[4];
	parseGrammer(pathIn, grammer);
	removeNullRules(buildNullSet(grammer), grammer);		
	removeOldNullRules(grammer[RULES], *(grammer[START].begin()));
	outputGrammer(pathOut, grammer);
}

void removeNullRules( set<char*> nullSet, set<char*>* grammer){

	set<char*>::iterator it;
	char* newRule;
	int nullAmount = 0;
	char* permList;
	char* rule;


	for( it = grammer[RULES].begin(); it != grammer[RULES].end(); it++){
		addNewRules( *it, nullSet, grammer[RULES]);
	}

	// If the start symbol is part of the NULL SET
	// Then add the rule S -> NULL_CHAR
	if( member(nullSet, *(grammer[START].begin()))) {
		newRule = new char[MAX_RULE_SIZE+1];
		strncpy(newRule, *(grammer[START].begin()), MAX_VAR_SIZE);
		strncat(newRule, " ", 1);
		strncat(newRule, NULL_CHAR, 1);
		if( !member( grammer[RULES], newRule)) {
			grammer[RULES].insert(newRule);
		}
		else{
			delete newRule;
		}

	}

}


int getNullAmount( char* rule,  set<char*> nullSet ){

	char tmp[MAX_VAR_SIZE];
	int length = 0;
	int nullAmount = 0;
	
	// goes until the end of the rule
	while( *rule ){
		// if what rules ptr is at is a variable
		// then it will get its length then we make
		// a tmp var and check if its a member of the null set
		// if it is then add 1 to null amount and
		// plus the ptr by the size of the variable
		if( (length = isVariable( rule ))){	
			strncpy(tmp, rule, length);
			*(tmp+length) = '\0';
			if( member( nullSet, tmp ) ){
				nullAmount++;
			}
			rule+=length;
		}
		else{
			rule++;
		}

	}
	return nullAmount;
}


//PRODUCES A NEW CHAR* MUST DELETE THE PTR IT RETURNS
char* getPermutationList( int nullAmount, char* rule ){

	int numNewRules = pow(2,nullAmount)-1;
	char* permList;
	
	if( numNewRules ){

		// size of the perm list is 2^nullAmount * nullAmount + 1
		// 2^nullAmount is the number of newRules generated 
		// *nullAmount takes in account each character produced
		// and +1 for the '\0' char
		permList = new char[numNewRules*nullAmount+1];
		char* ptr = permList;		
		int num;

		// Outter loop for is for producing the new rules
		// Turn each number from 0 to (2^nullAmount)-1 into binary
		// so you can use this to generate all possible permentions
		for(int i = 0; i < numNewRules; i++){
			num = i;
			for( int j = 0; j < nullAmount; j++){
				if( num%2 == 0){
					*ptr = '1';
				}
				else{
					*ptr = '0';
				}
				num/=2;
				ptr++;
			} 
		}	
		*ptr = '\0';	
	}	
	else{
		return NULL;
	}

	return permList;	

}

void addNewRules(char* production, set<char*> nullSet, set<char*>& rules){


	vector<char*> splitRule = splitProduction( production );
	vector<char*>::iterator itRule;
	int nullAmount = getNullAmount( getRulePtr(production), nullSet);
	int numNewRules = pow(2,nullAmount)-1;
	int size = 0;
	char* permList = getPermutationList( nullAmount, getRulePtr(production));
	char* newRule, *permListPtr = permList;
	char tmpRule[MAX_RULE_SIZE+1] = "\0";	

	
	for( int i = 0; i < numNewRules; i++){		
		itRule = splitRule.begin();
		while( ++itRule != splitRule.end() ){
			if( member( nullSet, *itRule) && *(permList++) == '0'){
				strncat(tmpRule, *itRule, strlen(*itRule));
			}
			else if( (size = isTerminal(*itRule)) ){
				strncat(tmpRule, *itRule, size);
			}
		}

			
	
		// if there is something in tmpRule
		if( *tmpRule ){
			newRule = new char[MAX_RULE_SIZE+1];
			
			// Copys the current var a space and the new rule
			// EX: S bA	
			strncpy(newRule, splitRule[0], strlen(splitRule[0])+1);
			strncat(newRule, " ", 1);
			strncat(newRule, tmpRule, MAX_RULE_SIZE);		

			if( !(member(rules, newRule)) ){
				rules.insert(newRule);
			}
			else{
				delete(newRule);
			}
			
			*tmpRule = '\0';
		}
	}	

	delete permListPtr;
} 


void removeOldNullRules(set<char*>& rules, char* start){

	set<char*>::iterator it;
	char* rule;
	
	for( it = rules.begin(); it != rules.end(); it++){
		if( !(varEqual(start, *it))){
			rule = getRulePtr(*it);
			if( strcmp(rule, NULL_CHAR) == 0 ){
				rules.erase(it);
			}
		}
	}
}

// ALGORITHM 4.2.1 (Page 108)
/*

input: context-free grammer G = (V, E, P, S)

1. NULL := { A | A -> Lamda (exist in) P }
2. repeat
	2.1. PREV := NULL
	2.2. for each variable A (exist in) V do
		if there is an A rule A -> w and w (exist in) PREV*, then
			NULL := NULL U {A}
until NULL = PREV
*/
set<char*> buildNullSet(set<char*>* grammer){
	
	set<char*> nullSet = initNullSet(grammer);
	set<char*> prevSet;
	
	set<char*>::iterator itVar;
	set<char*>::iterator itPro;

	//repeat
	do{
		// PREV := NULL
		unionSet( prevSet, nullSet );		
		// for each A (exist in) V
		for( itVar = grammer[VARIABLES].begin(); itVar != grammer[VARIABLES].end(); itVar++){
			// have to iterate through the rules to find ones such that A -> w and w exsit in PREV*
			for( itPro = grammer[RULES].begin(); itPro != grammer[RULES].end(); itPro++){
				// A -> w
				if( varEqual( *itVar, *itPro) ){
					// w (exist in) prevSet*
					if( ruleInPrev( getRulePtr(*itPro), prevSet) ){
						// NULL := NULL U {A}
						nullSet.insert(*itVar);
					}
				}
			}
		}
	}while( !compareSets( nullSet, prevSet ) );
	return nullSet;
}

bool ruleInPrev( char* rule, set<char*> prevSet ){
	
	char tmpVar[MAX_VAR_SIZE+1];
	char* currentPtr = rule;	
	int varSize = 0;	

	while( (varSize = isVariable(currentPtr)) ){

		strncpy(tmpVar, currentPtr, (varSize));
		*(tmpVar+varSize) = '\0';
		
		if(member(prevSet, tmpVar) == 0 ){
			return false;
		}	
	
		currentPtr += varSize;
	}
	// checks if the pointer has moved at all if it hasent then this is not a variable
	// other wise it has gone through the while loop succefully
	if( currentPtr == rule ){
		return false;
	}
	return true;


}

// { A | A -> NULL_CHAR (exist in) P }
set<char*> initNullSet( set<char*>* grammer){

	set<char*>::iterator it;
	set<char*> nullSet;

	char* newNullVar;
	
	for( it = grammer[RULES].begin(); it != grammer[RULES].end(); it++){
		if( strcmp( getRulePtr( *it ), NULL_CHAR) == 0 ){
			newNullVar = new char[MAX_VAR_SIZE];
			// Gets the lengtt of the var so when you use
			// strncpy it will only copy the variable
			strncpy(newNullVar, *it, variableLen(*it));	
			*(newNullVar + variableLen(*it)) = '\0';
			
			if( !(member(nullSet, newNullVar)), newNullVar){
				nullSet.insert(newNullVar);
			}
			else{
				delete(newNullVar);
			}

		}
	}	

	return nullSet;
}

