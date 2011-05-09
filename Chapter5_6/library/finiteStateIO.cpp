#include "finStateIO.h"
#include "lib.h"

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
void parseLine(char* line, std::set<char*>* finiteState);

void getStates(char* line, std::set<char*>& states);
void getAlphabet(char* line, std::set<char*>& alphabet);
bool getTransitions(char* line, std::set<char*>& transitions);
void getFinalStates(char* line, std::set<char*>& final);

int readFile(char* path, char* file);



using namespace std;
int main(){
	
	set<char*> finiteState[4];

	parseFiniteState("dfa.txt", finiteState); 	

}



void parseFiniteState(char* path, set<char*>* finiteState){

	char* p;
	char file[MAX_FILE_SIZE];
	char* line; 

	readFile(path, file);

	line = strtok_r(file, "\n", &p);

	while( line ){
		parseLine(line, finiteState);
		line = strtok_r(NULL, "\n", &p);
	}

	
}


void parseLine(char* line, set<char*>* finiteState){

	//cout << line << "--" << endl;
	if( getTransitions(line, finiteState[TRANSITIONS])){
		//getStates(line, finiteState[STATES]);
		//getAlhpabet(line, finiteState[ALPHABET]);
	}
	else{
		getFinalStates(line, finiteState[FINAL]);
	}

	displaySet(finiteState[TRANSITIONS]);

}




void getStates(char* line, std::set<char*>& states){


}
void getAlphabet(char* line, std::set<char*>& alphabet){



}

bool getTransitions(char* line, std::set<char*>& transitions){
	
	char* newTran = new char[MAX_TRAN_SIZE+1];

	
	if( *line != 'd' ){
		return false;
	}
	
	strncpy(newTran, line, strlen(line)+1);
	
	cout << newTran << "+_" << endl;

	insertIntoSet(transitions, newTran);
	
	
	return true;

}

void getFinalStates(char* line, std::set<char*>& final){




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





