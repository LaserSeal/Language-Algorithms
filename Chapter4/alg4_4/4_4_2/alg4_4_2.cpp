#include "lib.h"
#include "gramIO.h"
#include "../../main/chap4.h"

void removeUselessVar( std::set<char*> usefulVar, std::set<char*>* grammer);
std::set<char*> setDeriveTermString(std::set<char*>* grammer);
std::set<char*> initTermSet(std::set<char*> rules);
bool inPrevAlphabet( char* rule, std::set<char*> prevSet, std::set<char*> alphabet);

void removeUnReachable( std::set<char*> termSet, std::set<char*>* grammer);
std::set<char*> getReachable( std::set<char*>* grammer );

using namespace std;
/*int main(){


	alg4_4_2("../../grammers/grammerA.txt", "newGrammer.txt");	
	alg4_4_2("../../grammers/grammerA.txt", "newGrammer.txt");	
	alg4_4_2("grammer.txt", "newGrammer.txt");	
	alg4_4_2("grammer.txt", "newGrammer.txt");	
}*/


void alg4_4_2(char* pathIn, char* pathOut){
	set<char*> grammer[4];
	parseGrammer(pathIn, grammer);

	removeUselessVar( setDeriveTermString(grammer), grammer );
	
	outputGrammer(pathOut, grammer);
}


void removeUselessVar( set<char*> termSet, set<char*>* grammer){

	set<char*>::iterator itPro;
	set<char*>::iterator itRemove;

	itPro = grammer[RULES].begin();

	// A -> w | A -> w is a rule in P, A (exist in) TERM, and w (exist in) (TERM U ALPHABET)*
	while( itPro != grammer[RULES].end() ){
		if( !(inPrevAlphabet( getRulePtr(*itPro), termSet, grammer[ALPHABET])) ){
			itRemove = itPro;
			++itPro;
			grammer[RULES].erase(itRemove);
		}
		else{
			++itPro;
		}
	}

	interSet(grammer[VARIABLES], termSet);

}

/* Algorithm 4.4.2 (Page 117)

1. TERM := {A | there is a rule A -> w (exist in) P with w (exist in) ALPHABET*}
2. repeat
	2.1. PREV := TERM
	2.2. for each variable A (exist in) V do
		if there is an A rule A -> w and w (exist in) (PREV U ALPHABET)* then
			TERM := TERM U {A}
until PREV = TERM

*/

set<char*> setDeriveTermString(set<char*>* grammer){

	// TERM := {A | there is a rule A -> w (exist in) P with w (exist in) ALPHABET*}
	set<char*> termSet = initTermSet(grammer[RULES]);
	set<char*> prevSet;
	set<char*>::iterator itRule;
	
	// repeat
	do{
		// PREV := TERM
		unionSet(prevSet, termSet);
		// for each variable A (exist in) V
		for( itRule = grammer[RULES].begin(); itRule != grammer[RULES].end(); itRule++){
			// if there is A rule A -> w and w (exist in) (PREV U ALPHABET)* 
			if(inPrevAlphabet( getRulePtr(*itRule), prevSet, grammer[ALPHABET])){
				// TERM := TERM U {A}
				insertVariable(termSet, *itRule);
			}
		}	
	// until PREV = TERM
	}while( !(compareSets(prevSet, termSet)) );

	return termSet;
}	



bool inPrevAlphabet(char* rule, set<char*> prevSet, set<char*> alphabet){

	set<char*> tmpSet;
	unionSet(tmpSet, prevSet);
	unionSet(tmpSet, alphabet);
	
	char tmpString[MAX_VAR_SIZE+1];

	int size;

	// while the rule hasent reached the end '\0'
	while(*rule){
		
		// Relies on short-circuit evalutation,
		// IF the rule is currently a Terminal it will be true and stop
		// the evaulation of second part so size wont get a 0
		// ELSE it is a variable and it will get a value on the second part
		if( (size = isTerminal(rule)) || (size = isVariable(rule)) ){
			strncpy(tmpString, rule, size);
			*(tmpString+size) = '\0';
			// if its not a member of the tmp set then fail
			// tmpSet = (prevSet U alphabet)
			if( !(member(tmpSet, tmpString))){
				return false;
			}
			// move the pointer down size times
			rule += size;
		}
		else{
			rule++;
		}
	}
	// checks if we went through the entire rule
	if(!(*rule)){
		return true;
	}
	return false;
	


}

// TERM = [A | A -> w where w is some combonation of the alphabet]
set<char*> initTermSet(set<char*> rules){

	set<char*> termSet;
	set<char*>::iterator it;
	char* rulePtr;
	char* newVar;
	int termSize;
	
	for( it = rules.begin(); it != rules.end(); it++){
		rulePtr = getRulePtr(*it);
		// Keeps going through the rule until it hits
		// '\0' or variable which will make isTerminal 
		// return a 0
		while( (termSize = isTerminal( rulePtr )) ){
			rulePtr += termSize;	
		}
		// checks if rulePtr has reached the end '\0'
		// if it has then the entire rule is a terminal
		if( !(*rulePtr) ){
			newVar = new char[MAX_VAR_SIZE];
			strncpy(newVar, *it, isVariable(*it));
			termSet.insert(newVar);
		}
		
	}	
	

	return termSet;
}




