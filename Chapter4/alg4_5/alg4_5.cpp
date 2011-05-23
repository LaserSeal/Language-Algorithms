#include "gramIO.h"
#include "gramLib.h"
#include "../main/chap4.h"

void convertToChomsky( std::set<char*>* grammer, std::set<char*>* newGrammer);

void removeTerminals( std::set<char*>* grammer, std::set<char*>* newGrammer);

void addNewRule( char* var, char* rule, std::set<char*>& rules);

void splitNewRules(std::set<char*>* newGrammer);
void produceNewRules(std::vector<char*> splitRule, std::set<char*>& rules, std::set<char*>& var);


bool singleRule(std::set<char*> rules, char* production);
char* generateNewVar( char* terminal, std::set<char*> variables, std::set<char*> rules);
char* newTVar(std::set<char*> variables);

using namespace std;
/*int main(){
	
	set<char*> grammer[4];
	parseGrammer("grammer.txt", grammer);
	if( singleRule(grammer[RULES], "A a")){
		cout << "?" << endl;
	}
	else{
		cout << "nope" << endl;
	}
	
	alg4_5("grammer.txt", "newGrammer.txt");

}*/


void alg4_5(char* pathIn, char* pathOut){

	set<char*> newGrammer[4];
	set<char*> grammer[4];
	parseGrammer(pathIn, grammer);
	
	convertToChomsky(grammer, newGrammer);	

	displayGrammer(newGrammer);	
	

	outputGrammer(pathOut, newGrammer);
}

/*

G  = (V, ALPHABET, P, S)
G' = (V', ALPHABET, P', S')
Chomsky Normal Form Rules:

  i) A -> BC
 ii) A -> a, or
iii) S -> Lambda

where B, C (exist in) V - {S}



CASE:

S -> Lambda
-- If this rule exist add to P'

A -> a (singal terminal)
-- If this rule exist add to P'

A -> w
where w (exist in) (( V U ALPHABET) - {S} )* and length(w) > 1
-- If this then w must contain variables and terminals
-- To fix this we much replace all terminals with variables
-- and add new variables that are eqivalent to each terminal
*/

void convertToChomsky( set<char*>* grammer, set<char*>* newGrammer){


	// Both of these are unchanged in producing CNF
	unionSet(newGrammer[ALPHABET], grammer[ALPHABET]);
	unionSet(newGrammer[START], grammer[START]);
	unionSet(newGrammer[VARIABLES], grammer[VARIABLES]);	


	// Add any rule such that S -> Lambda or A -> w where w is a singal terminal symbol

	removeTerminals( grammer, newGrammer);
	splitNewRules(newGrammer);
		
}


void removeTerminals(set<char*>* grammer, set<char*>* newGrammer){
	
	char* newVar;
	char* newRule;
	char tmpRule[MAX_RULE_SIZE+1] = "\0";
	vector<char*> proVec;
	
	set<char*>::iterator itPro;



	for( itPro = grammer[RULES].begin(); itPro != grammer[RULES].end(); itPro++){
		proVec = splitProduction(*itPro);
		for( int i = 1; i < proVec.size(); i++){
		
			// If its a terminal and there are more then just a single terminal
			// FAILS IF A -> a
			if( isTerminal(proVec[i]) && proVec.size() > 2){
				newVar = generateNewVar(proVec[i], newGrammer[VARIABLES], newGrammer[RULES]);	
				cout << newVar << " | " << *itPro << endl;
				addNewRule(newVar, proVec[i], newGrammer[RULES]);
				strncat(tmpRule, newVar, MAX_VAR_SIZE);	
				insertIntoSet(newGrammer[VARIABLES], newVar);	
			}
			// Else its a variable thats not in the null set or a terminal
			else{
				strncat(tmpRule, proVec[i], MAX_RULE_SIZE);
			}
		}	
		// New rule	
		newRule = new char[MAX_RULE_SIZE+1];
		strncpy(newRule, proVec[0], strlen(proVec[0])+1);
		strncat(newRule, " ", 1);
		strncat(newRule, tmpRule, MAX_RULE_SIZE);		
		insertIntoSet(newGrammer[RULES], newRule);
		*tmpRule = '\0';
	}		
}


void splitNewRules(set<char*>* newGrammer){
	
	vector<char*> splitRule;
	set<char*> tmpRules;
	set<char*>::iterator itRule;
	set<char*>::iterator itTmp;
	char* newVar;
	char* newRule;

	unionSet(tmpRules, newGrammer[RULES]);

	for( itRule = newGrammer[RULES].begin(); itRule != newGrammer[RULES].end(); itRule++){
		splitRule = splitProduction(*itRule);
		if( splitRule.size() > 3 ){
			produceNewRules(splitRule, tmpRules, newGrammer[VARIABLES]);
			tmpRules.erase(*itRule);
		}
	
	
	}

	// Keep everything they have in common
	interSet(newGrammer[RULES], tmpRules);
	// Only keep the difference of tmpRules to newGrammer
	diffSet(tmpRules, newGrammer[RULES]);
	// Unions the intersection (tmpRules and newGrammer) have in common with the difference of (tmpRules and newGrammer)
	unionSet(newGrammer[RULES], tmpRules);
	displaySet(tmpRules);


}

void produceNewRules(vector<char*> splitRule, set<char*>& rules, set<char*>& variables){

	char* newVar;
	char* newRule;
	char* changedRule;
	int size = 0;
	

	while( (size = splitRule.size()) > 3 ){
			if( (newVar = newTVar(variables)) ){
				newRule = new char[MAX_RULE_SIZE+1];
				strncpy(newRule, newVar, strlen(newVar)+1);
				strncat(newRule, " ", 1);
				strncat(newRule, splitRule[size-2], MAX_RULE_SIZE);
				strncat(newRule, splitRule[size-1], MAX_RULE_SIZE);
			
				// Pops last 2 off
				splitRule.pop_back();
				splitRule.pop_back();
				splitRule.push_back(newVar);
	
				cout << newRule << endl;
				rules.insert(newRule);
				variables.insert(newVar);
			}
			else{
				cout << "To many new T varaibles...." << endl;
				return;
			}
			
	}
	
	changedRule = flattenProductVector(splitRule);
	rules.insert(changedRule);
}

char* newTVar(set<char*> variables){
	
	char* newVar = new char[MAX_VAR_SIZE+1];
	char* ptr = (newVar+1);
	int size = 2;
	strncpy(newVar, "T0", 2);
	*(newVar+2) = '\0';

	// Keeps going until it makes a var
	// Will stop before it makes a var to large to fit in the array
	// But will create an infinate loop, add still add one to the array
	while( member(variables, newVar) ){
		if( *ptr == '9'){
			strncat(newVar, "0", 1);
			ptr++;
			size++;
			*(ptr+1) = '\0';
		}
		else{
			*ptr += 1;
		}
		if( size > MAX_VAR_SIZE){
			return NULL;
		}
	}
	
	return newVar;	
}

void addNewRule(char* var, char* rule, set<char*>& rules){
	char* newRule = new char[MAX_RULE_SIZE+1];
	strncpy(newRule, var, strlen(var)+1);
	strncat(newRule, " ", 1);
	strncat(newRule, rule, strlen(rule));
	insertIntoSet( rules, newRule);
}

// RETURNS A PTR TO THE NEW VAR
char* generateNewVar(char* terminal, set<char*> variables, set<char*> rules){

	// check if there is a rule that goes to the terminal already
	set<char*>::iterator itPro;
	vector<char*> splitRule;
	char* newVar = new char[MAX_VAR_SIZE+1];
	char* rulePtr;
	int varSize = 0;		

	// checks if there exsit a rule that goes to a terminal already
	for( itPro = rules.begin(); itPro != rules.end(); itPro++){
		rulePtr = getRulePtr(*itPro);			
		if( strcmp(rulePtr, terminal) == 0 && singleRule(rules, *itPro)){	
			varSize = isVariable(*itPro);
			strncpy(newVar, *itPro, varSize);
			*(newVar+varSize) = '\0';
			 return newVar;
		}
			
	}

	// ELSE generate a new one
	*(newVar) = (char)toupper(*terminal);
	*(newVar+1) = '\0';
	strncat( newVar, (terminal+1), MAX_VAR_SIZE);
		
	// Need to check if at any point im trying to copy past MAX_VAR_SIZE
	do{
		strncat(newVar, "0", 1);
	}while( member(variables, newVar) );

	return newVar;
}


// Make sures that the rule can only go the terminal
bool singleRule(set<char*> rules, char* production){
	
	set<char*>::iterator itRule;
	int varSize = isVariable(production);
	int lessOne = 0;	
	char tmpVar[MAX_VAR_SIZE+1];
	strncpy(tmpVar, production, varSize);
	*(tmpVar+varSize) = '\0';

	
	for( itRule = rules.begin(); itRule != rules.end(); itRule++){
		cout << tmpVar << " | "<<*itRule << endl;
		if( lessOne > 1 ){
			return false;
		}
		else if( varEqual(tmpVar, *itRule)){
			lessOne++;
		}
	}

	return true;
}














