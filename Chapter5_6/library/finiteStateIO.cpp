#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>


#define MAX_FILE_SIZE 512

/*
M = {Q, E, D, q0, F}
Q  :: finite set of states
E  :: alphabet
D  :: transition funcitons
q0 :: start state
F  :: set of final or accepting states

D is a total function such Q x E to Q
meaning, (Q, E) to Q

Examples:
Q{ q0, q1, q2, ..., qn }
E{ a,b,c,a23,v23 }
D{ d(q0, a) = q1
   d(q0, b) = q0
   d(q1, a) = q1
   d(q1, b) = q0 }
F{ q1 }

*/

void parseFiniteState(char* path, std::set<char*>* finiteState);
int readFile(char* path, char* file);



using namespace std;
int main(){
	
	set<char*> finiteState[4];

	parseFiniteState("dfa.txt", finiteState); 	

}



void parseFiniteState(char* path, set<char*>* finiteState){

	char file[MAX_FILE_SIZE];

	readFile(path, file);

	cout << file << endl;
	
}



int readFile(char* path, char* file){

	int length;
	ifstream is;

	is.open(path);

	if( is.is_open() && is.good() ){
		is.seekg(0, ios::end);	
		length = is.tellg();
		is.seekg(0, ios::beg);	
	
		is.read(file, length);
	}
	else{

		cerr << "Bad file name: " << path << endl;
	}
	
	is.close();
	return length;
}





