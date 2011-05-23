#include "gramLib.h"
#include "gramIO.h"

void alg4_4_4(char* pathIn, char* pathOut);

std::set<char*> getReachable( std::set<char*>* grammer );
void addToReach( char* rule, std::set<char*>& reachSet);

using namespace std;
/*int main(){
	alg4_4_4("grammer.txt", "newGrammer.txt");	
}*/

void alg4_4_4(char* pathIn, char* pathOut){

	set<char*> grammer[4];
	parseGrammer(pathIn, grammer);

	interSet(grammer[VARIABLES], getReachable(grammer));
	
	outputGrammer(pathOut, grammer);
}

/* Algorithm 4.4.4 - Page 119

input: context-free grammer G = (V, E, P, S)

1. REACH := {S}
2. PREV := {}
3. repeat
	3.1. NEW  := REACH - PREV
	3.2. PREV := REACH
	3.3 for each variable A (exist in) NEW do
		for each rule A -> w do add all variables in w to REACH
unil REACH = PREV
*/


set<char*> getReachable( set<char*>* grammer){


	set<char*> reachSet;	
	set<char*> newSet;
	set<char*> prevSet;
	
	set<char*>::iterator itVar;
	set<char*>::iterator itPro;

	reachSet.insert(*(grammer[START].begin()));	

	do{
		unionSet(newSet, reachSet);
		diffSet(newSet, prevSet);
		
		unionSet(prevSet, reachSet);
		

		for( itVar = newSet.begin(); itVar != newSet.end(); itVar++){
			for( itPro = grammer[RULES].begin(); itPro != grammer[RULES].end(); itPro++){
				if( varEqual(*itVar, *itPro) ){
					addToReach( getRulePtr(*itPro), reachSet);
				}
			}
		}
	

	}while( !(compareSets(reachSet, prevSet)));

	return reachSet;

}


void addToReach( char* rule, set<char*>& reachSet){

	int size;
	
	while(*rule){
		if( (size = isVariable(rule)) ){
			insertVariable(reachSet, rule);
			rule += size;
		}
		else{
			rule++;
		}
	}

}

