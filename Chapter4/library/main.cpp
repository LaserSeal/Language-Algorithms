#include <iostream>
#include "gramIO.h"
#include "lib.h"


using namespace std;
int main(){

	vector<char*> splitRule;

	set<char*> grammer[4];
	set<char*>::iterator it;

	parseGrammer("grammer2.txt", grammer);	
	for( it = grammer[RULES].begin(); it != grammer[RULES].end(); it++){
		splitRule = splitProduction(*it);
		cout << flattenProductVector(splitRule) << "--" << endl;
	}

/*	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	
	parseGrammer("grammer.txt", grammer);	*/
}
