#include "finStateIO.h"
#include "lib.h"



using namespace std;
int main(){

	set<char*> finiteState[4];
	parseFiniteState("dfa.txt", finiteState);
	

	vector<char*> split;
	vector<char*>::iterator itVec;
	set<char*>::iterator it;

	for( it = finiteState[TRANSITIONS].begin(); it != finiteState[TRANSITIONS].end(); it++){
		cout << *it << endl;
		split = splitTransition(*it);
		for( itVec = split.begin(); itVec != split.end(); itVec++){
			cout << *itVec << endl;
		}
	}
		
/*
	displaySet(finiteState[0]);
	displaySet(finiteState[1]);
	displaySet(finiteState[2]);
	displaySet(finiteState[3]);


	cout << newTransition("q1", "b", "q2") << endl;
*/
}




