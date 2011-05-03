
//##########################################
// -Author: Brandon Schaefer
// -Created: 5/14/11
// -File Name: grammerIO.cpp 
//##########################################
#include "lib.h"
#include "gramIO.h"


using namespace std;


//##############################
// Start of Reading in Grammer from File
//##############################


char* readGrammer(char* path){

	// MAX_FILE_SIZE is 256
	char* tmpPtr = new char[MAX_FILE_SIZE];

	// Does 2 things, gets the raw file data and the size of the file
	// We put it in a tmpPtr so we can allocate a new array.
	int size = readFile(path, tmpPtr);
	
	// readFile returns the size of the file so we can now
	// make an array to fit the exact size of the file +1 for '\0'
	char* file = new char[size+1];
	strncpy(file, tmpPtr, size+1);
	
	// Delete the tmp ptr
	delete tmpPtr;
	return file;
}

int readFile(char* path, char* file){	
	int length;
	ifstream is;


	is.open(path);
	
	if( is.is_open() && is.good()){
		// Gets the length of the file 
		is.seekg(0, ios::end);
		length = is.tellg();
		is.seekg(0, ios::beg);
	
		// Takes the raw data from the file and put it in file.
		is.read(file, length);
		/* DOUBLE CHECK THAT I DONT NEED TO BE OUT SIDE THE IF */
	}
	else{
	 	cerr << "Bad File Name: " <<  path << endl;
		throw;
	}

	is.close();
	return length;
}

void freeFile(char* file){
	delete(file);
}


//##############################
// ---------------- End of reading in a grammer from a file
//##############################




//##############################
// -------- Start of ParsingGrammer Functions into a set ------------ //
//##############################
// Sample use:
/*
	// You have to allocate space for grammer
	std::set<char*> grammer[3];
	parseGrammer("grammer.txt", grammer);
	
	displaySet(grammer[VARIABLES]);	
	cout << "---- END OF VARS ----" << endl;
	displaySet(grammer[ALPHABET]);
	cout << "---- END OF ALPH ----" << endl;
	displaySet(grammer[RULES]);

*/


// The grammer is a set of sets in the form of <V, A, P>
// V = The variables, the set non-terminals
// A = The alaphabet, the set of all possible terminals
// P = The productions, the 
void parseGrammer( char* path, set<char*>* grammer ){
	
	char* file = readGrammer(path);
	char* p;
	char* line = strtok_r(file, "\n", &p);

	
	// Gets the start symbol
	insertVariable( grammer[START], line);	

	while( line ){
		parseLine(grammer, line);		
		line = strtok_r(NULL, "\n", &p);
	}
		

	freeFile(file);
}


void parseLine( set<char*>* grammer, char* line){
	char* var = getVariable(grammer[VARIABLES], line);
	if( var ){
		getAlphabet(grammer[ALPHABET], line);
		getRules(grammer[RULES], line, var);
	}
}

/*################## FIX ME ######################### USE NEW isVariable FUNCTION */

// Stores the var the grammer set and also returns a pointer to the var thats found
char* getVariable( set<char*>& variables, char* line){

	char* newVar;

	if( isVariable(line)){
	 	newVar = insertVariable(variables, line);
		return newVar;
	}
	return NULL;	
}


//get any letter that is lower case which is a terminal meaning there can only be 26 different terminals
void getAlphabet(set<char*>& alphabet, char* line){
	char* newAlph, *linePtr = line;
	int termSize = 0;

	while(*linePtr){
		if(( termSize = isTerminal(linePtr))){
			newAlph = new char[termSize+1];
			*(newAlph+termSize) = '\0';
			strncpy(newAlph, linePtr, termSize);	
			linePtr+= termSize;

			// Here so if already in set we need to free the memory
			// Otherwise mem leak.
			if(!member(alphabet, newAlph)){
				alphabet.insert(newAlph);
			}
			else{
				delete(newAlph);
			}

		}
		else{
			linePtr++;
		}
		// Moves ptr to next term or var.

	}

}

void getRules( set<char*>& rules, char* line, char* var){
	char* rule, *ptr, *p;

	// Skips of var until it hits the ->, 
	// then it eats up all the empty spaces
	while(*line && *(line++) != '>');
	while(*line && *(++line) == ' ');

	ptr = strtok_r(line, "| ", &p);
	
	
	while(ptr){
		rule = new char[MAX_RULE_SIZE];
		strncpy(rule, var, MAX_VAR_SIZE);
		strncat(rule, " ", 1);
		strncat(rule, ptr, MAX_RULE_SIZE);
		rules.insert(rule);
		ptr = strtok_r(NULL, "| ", &p);
	}
}


//##############################
// ------- END OF PARSING AND READING A GRAMMER IN ----------------
//##############################


//##############################
// ------ START OF GRAMMER OUTPUT TO A FILE  -------------------------
//##############################

void outputGrammer( char* file, set<char*>* grammer){
	
	set<char*>::iterator itVar;
	char* start = *(grammer[START].begin());
	char outputStream[MAX_FILE_SIZE] = "";

	insertStart(grammer, outputStream);

		
	// Iterates through the variables then goes to insertRules to get the productions rules for each
	// variable
	for( itVar = grammer[VARIABLES].begin(); itVar != grammer[VARIABLES].end(); itVar++){
		if( strcmp(start, *itVar) != 0 ){
			strncat(outputStream, *itVar, MAX_VAR_SIZE);
			strncat(outputStream, " -> ", 4);	
			insertRules( *itVar, grammer[RULES], outputStream);
			strncat(outputStream, "\n", 1);
		}
	}	
	sendStream( file, outputStream );

/*
	grammer[3].clear();
	grammer[2].clear();
	grammer[1].clear();
	grammer[0].clear();*/
}


void insertStart( set<char*>* grammer, char* outputStream){
	
	char* start = *(grammer[START].begin());
	
	strncat(outputStream, start, MAX_VAR_SIZE);
	strncat(outputStream, " -> ", 4);
	insertRules( start, grammer[RULES], outputStream);
	strncat(outputStream, "\n", 1);

}


// Takes a variable and the rules from the grammer and finds the rules of the variable 
// and adds it the outputStream char* so it can be outputed to a file later.
void insertRules( char* variable, set<char*> rules, char* outputStream ){
	
	set<char*>::iterator itRule;
	char* ptr;

	for( itRule = rules.begin(); itRule != rules.end(); itRule++){
		if( varEqual( variable, *itRule) ){
			strncat(outputStream, getRulePtr(*itRule), MAX_RULE_SIZE);
			strncat(outputStream, " | ", 3);
		}

	}
	// removes the extra bar that the end, and the extra 0
	//*(strrchr(outputStream, '|')-1) = '\0';
	if( (ptr = strrchr(outputStream, '|')) != NULL ){
		*(ptr-1) = '\0';
	} 
}

// Takes the outputStream made in outputGrammer(...) and sends it to a specified file.
void sendStream( char* path, char* outputStream ){
	
	int size = strlen(outputStream);

	ofstream outfile( path );
	if( outfile.is_open() && outfile.good()){
	
		outfile.write(outputStream, size);
	}	
	else{
		cerr << "Error in opening file: " << path << endl;
		throw;
	}
	outfile.close();
}


//##############################
// End of output grammer functions
//##############################
