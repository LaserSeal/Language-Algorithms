#include "gramIO.h"
#include "gramLib.h"
#include "lib.h"
#include "../main/chap4.h"
#include <map>
#include <stdlib.h>
#include <time.h>


void convertToGBN(std::set<char*>* grammer);

bool ruleViolation(char* production, std::map<int, char*> numbers);

void assignNumbers(std::set<char*> variables, char* start, std::map<int, char*>& numbers);

std::set<char*> lemma4_1_3(char* production, std::set<char*>& rules);

using namespace std;
void alg4_8(char* pathIn, char* pathOut){


	srand( time(NULL) );

	set<char*> grammer[4];
	
	alg4_7(pathIn, pathIn);

	parseGrammer(pathIn, grammer);		

	convertToGBN(grammer);	
	
	set<char*>::iterator it, it2;
	int tmp = 0;
	
/*
	for( it = grammer[VARIABLES].begin(); it != grammer[VARIABLES].end(); ++it){
		for( it2 = grammer[RULES].begin(); it2 != grammer[RULES].end(); ++it2){
			if( varEqual(*it, *it2) ){
				tmp++;
			}
		}
		cout << "Var: " << *it << " has " << tmp << " rules" << endl;
		tmp = 0;
	}*/
	

	outputGrammer(pathOut, grammer);

	freeCont(grammer[3]);
	freeCont(grammer[2]);
	freeCont(grammer[1]);
	freeCont(grammer[0]);
}

/* Greibach Normal Form

It is GNF if each of the rules follow one of these rules:
A -> aA1A2...An
A -> a
S -> S

where a (exist in) E and Ai (exist in) V - {S} for i = 1,2,...,n

We will remove direct left recursion from a G in chomsky normal form
so the rules will follow one of these rules:
A -> BC
A -> a
S -> $

Now all we have to replace are A -> BC, with lemma 4.1.3

P' = ( P - {A -> uBv}) U {A -> uw1v | uw2v | ... | uwnv}


*/


void convertToGBN(set<char*>* grammer){
	
	map<int, char*> numbers;
	
	assignNumbers(grammer[VARIABLES], *(grammer[START].begin()), numbers);

	/* 

	Loop until all uphold the rule
	S -> $
	A -> aw, w (exist in) V*
	A -> Bw, w (exist in) V*, and the number assgined to B is > then A
	
	loop 1-numbers.size();
	char* currentVar = (find the next i);
	for( it = rules....++it){
		removeDLR(grammer);
		if( varEqual( curVar, *it) && ruleViolation(*it, numbers){
			lemma4_1_3(*it, grammer[RULES]);
		}
	}
	*/

	
	set<char*> newRules;
	set<char*>::iterator itPro, itVar;
	set<char*>::iterator end = grammer[RULES].end();
	set<char*>::iterator tmp;
	char* curVar;
	int numSize = numbers.size();
	

	for( int i = 1; i <= numSize; i++){	
		curVar = numbers[i];
		for( itPro = grammer[RULES].begin(); itPro != end ;){
			if( varEqual(curVar, *itPro) && ruleViolation(*itPro, numbers)){
				tmp = itPro;
				++itPro;
				unionSet(newRules, lemma4_1_3(*tmp, grammer[RULES]));
			}
			else{
				++itPro;
			}
		}
		unionSet(grammer[RULES], newRules);
		newRules.clear();
		alg4_7_GNF(grammer, curVar);
	}
	
	// Now have to keep applying lema4_1_3 until all vars are in the form of:
	// A -> aw, w (exist in) V*
	
	/*

	for( itVar ... ++itVar){
		for( itPro ... ++itPro){
			if( varEqual( *itVar, *itPro) && isVariable(getRulePtr(*itPro) ){
				lemma4_1_3(
			}
		}
	}
	*/

	for( itVar = grammer[VARIABLES].begin(); itVar != grammer[VARIABLES].end(); ++itVar){
		for( itPro = grammer[RULES].begin(); itPro != grammer[RULES].end();){
			if( varEqual( *itVar, *itPro) && isVariable(getRulePtr(*itPro)) ){
				tmp = itPro;
				++itPro;
				unionSet(newRules, lemma4_1_3(*tmp, grammer[RULES]));
			}
			else{
				++itPro;
			}
			unionSet(grammer[RULES], newRules);
			newRules.clear();
		}
	}

	
	map<int, char*>::iterator it;

	cout << "Mapping of the Variables:" << endl;	
	for( it = numbers.begin(); it != numbers.end(); ++it){
		cout << it->first << " | " << it->second << endl;
	}
}

bool ruleViolation(char* production, map<int, char*> numbers){

	char* rulePtr = getRulePtr(production);
	char* tmpNull = (rulePtr-1);
	*tmpNull = '\0';
	int size = isVariable(rulePtr);
	int curVarNum;
	int ruleVarNum;

	map<int, char*>::iterator it;

	// check for A -> Bw
	for( it = numbers.begin(); it != numbers.end(); ++it){
		if( strncmp(it->second, production, MAX_VAR_SIZE) == 0 ){
			curVarNum = it->first;
		}
		if( strncmp(it->second, rulePtr, size) == 0 ){
			ruleVarNum = it->first;
		}
	}

	*tmpNull = ' ';
	if( curVarNum > ruleVarNum ){
		return true;
	}	
	return false;
}


void assignNumbers(set<char*> variables, char* start,  map<int, char*>& numbers){

	set<char*>::iterator itVar;
	int i = 2;

/*
	numbers.insert(std::pair<int, char*>(1,start));
	numbers.insert(std::pair<int, char*>(2,"A"));
	numbers.insert(std::pair<int, char*>(3,"B"));
	numbers.insert(std::pair<int, char*>(4,"C"));
	numbers.insert(std::pair<int, char*>(5,"D"));
*/
	numbers.insert(std::pair<int, char*>(1,start));

	for( itVar = variables.begin(); itVar != variables.end(); ++itVar){
		if( strncmp( *itVar, start, MAX_VAR_SIZE) != 0 ){
			numbers.insert(std::pair<int, char*>(i, *itVar));
			i++;
		}
	}

}



// P' = ( P - {A -> uBv} ) U { A -> uw1v | uw2v | ... | uwnv
set<char*> lemma4_1_3(char* production, set<char*>& rules){

	set<char*> newRules;
	set<char*>::iterator itPro;
	char* rulePtr = getRulePtr(production);
	char* newRule;
	int size = isVariable(rulePtr);



	//{ A -> uw1v | uw2v | ... | uwnv }	
	for( itPro = rules.begin(); itPro != rules.end(); ++itPro ){
		if( strncmp(rulePtr, *itPro, size) == 0 ){
			newRule = new char[MAX_RULE_SIZE+1];
			// Copys the prdocutions var + the space
			strncpy(newRule, production, (rulePtr-production));
			*(newRule+(rulePtr-production)) = '\0';
			//copys thes new rule B -> w to  A -> uwv
			strncat(newRule, getRulePtr(*itPro), MAX_RULE_SIZE);
			//copys the rest of the rule v to uw, and skips the
			// var we are repalcing
			strncat(newRule, (rulePtr+size), MAX_RULE_SIZE);
			insertIntoSet(newRules, newRule);	
		}
	}
	
	//( P - {A -> uBv} )
	for( itPro = rules.begin(); itPro != rules.end(); ++itPro){
		if(strncmp(production, *itPro, MAX_RULE_SIZE) == 0){
			rules.erase(*itPro);
			itPro = (--rules.end());
		}
	}
	// The union happens by just removing the old rule and inserting the new rules

	return newRules;
}





