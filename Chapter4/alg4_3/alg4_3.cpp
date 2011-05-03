#include <set>
#include <iostream>
#include <stdio.h>
#include "lib.h"
#include "gramIO.h"
#include "../main/chap4.h"


int chainRule(std::set<char*> var, char* currVar, char* production);
std::set<char*> deriveChainRule(char* variable, std::set<char*>* grammer);
void updateGrammer( std::set<char*> chainRules, std::set<char*>* grammer, char* curVar);
void addNewRule( std::set<char*>& rules, char* rule, char* curVar);
void removeOldChain( std::set<char*>* grammer );

using namespace std;
/*int main(){

}*/

void alg4_3(char* pathIn, char* pathOut){

	set<char*> grammer[4];
	set<char*> chainX;
	

	parseGrammer(pathIn, grammer);
	
	set<char*>::iterator it;

	// Goes through all the variables and gets the chain rules for them
	// then it updates its production rules with new ones
	// NOTE:
	// generating rules compared to adding them do not effect each other
	// since getting chain rules is dependent on other chain rules, since
	// we dont add any new ones they dont effect each other.
	for( it = grammer[VARIABLES].begin(); it != grammer[VARIABLES].end(); it++){
		chainX = deriveChainRule(*it, grammer);
		updateGrammer( chainX , grammer, *it );
	}
	// Remove all the chain rules after producting all new rules
	removeOldChain(grammer);	
	
	outputGrammer(pathOut, grammer);

}

// 4.3.1
/*

input: context-free grammer G = (V, E, P, S)

1. CHAIN(A) := {A}
2. PREV := CHAIN(A)
3. repeat
	3.1. NEW := CHAIN(A) - PREV
	3.2. PREV := CHAIN(A)
	3.3. for each variable B (exist in) NEW do
		for each rule B -> C do
			CHAIN(A) := CHAIN(A) U {C}
until CHAIN(A) = PREV
*/
set<char*> deriveChainRule(char* variable, set<char*>* grammer){
	set<char*> chainX;
	set<char*> prevSet;
	set<char*> newSet;
	
	set<char*>::iterator itPro;
	set<char*>::iterator itNew;	

	chainX.insert(variable);

	do{
		unionSet(newSet, chainX);
		diffSet(newSet, prevSet);
		
		unionSet(prevSet, chainX);
		for( itNew = newSet.begin(); itNew != newSet.end(); itNew++){
			for( itPro = grammer[RULES].begin(); itPro != grammer[RULES].end(); itPro++){
				if( chainRule(grammer[VARIABLES], *itNew, *itPro) ){
					insertVariable(chainX, getRulePtr(*itPro));
				}
			}

		}
	
	}while( !(compareSets( chainX, prevSet)) );	

	
	return chainX;
}


void updateGrammer( set<char*> chainX, set<char*>* grammer, char* curVar){
	set<char*>::iterator itChainX;
	set<char*>::iterator itRules;

	// The for loop is i) on page 115 ( B exist in CHAIN(A) )
	for( itChainX = chainX.begin(); itChainX != chainX.end(); itChainX++){
		// This for loop is for ii) ( B -> ( w exist in P ) )
		for( itRules = grammer[RULES].begin(); itRules != grammer[RULES].end(); itRules++){
			if( varEqual( *itChainX, *itRules ) ){
				if( member( grammer[VARIABLES], getRulePtr(*itRules)) == 0){
					addNewRule(grammer[RULES], *itRules, curVar);
				}
			} 	

		}
	}	

}

void addNewRule(set<char*>& rules, char* rule, char* curVar){
	char* newRule = new char[MAX_RULE_SIZE+1];
	
	strncpy(newRule, curVar, MAX_VAR_SIZE);
	strncat(newRule, (getRulePtr(rule)-1), MAX_RULE_SIZE);
	
	// AGAIN INSERT IS NOT REMOVING DUBLICATES
	if( member( rules, newRule ) == 0 ){	
		rules.insert(newRule);
	}
	else{// if(!newRule){
		delete newRule;
	}
}
	
// This just goes through and removes the first chain rules in the gammer //
void removeOldChain( set<char*>* grammer){

	set<char*>::iterator itRules;
	set<char*>::iterator itTmp;
	
	itRules = grammer[RULES].begin();
	
	while(itRules != grammer[RULES].end()){
		if( member( grammer[VARIABLES], getRulePtr(*itRules)) ){
			itTmp = itRules;
			++itRules;
			grammer[RULES].erase(*itTmp);
		}
		else{
			++itRules;
		}


	}
}

// For each production that is of the currt var 
int chainRule(set<char*> variable, char* currVar, char* production){
	// if production rule has currVar
	// and productions rule is a chain rule return 1

	if( varEqual(currVar, production) ){
		if( member(variable, getRulePtr(production)) == 1){
			return 1;
		}
	}
	return 0;
}


