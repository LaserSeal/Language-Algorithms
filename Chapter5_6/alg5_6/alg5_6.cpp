#include "finStateIO.h"
#include "lib.h"



using namespace std;
int main(){

	set<char*> finiteState[4];
	parseFiniteState("dfa.txt", finiteState);
	

	displaySet(finiteState[0]);
	displaySet(finiteState[1]);
	displaySet(finiteState[2]);
	displaySet(finiteState[3]);
}



