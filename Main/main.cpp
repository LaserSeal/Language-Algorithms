
#include <stdio.h>
#include <iostream>
#include <string.h>
//#include "chap4.h"
#include "chap5_6.h"

void checkCommand(char* buf, char* ptr);

using namespace std;
int main(){

	char* line;
	char* p;
	char buf[80];	

	while( (fgets(buf, 80, stdin)) != NULL ){
			line = strtok_r(buf, " \n", &p);
			checkCommand(line, p);	
/*			while(line){
				line = strtok_r(NULL, " \n", &p);
			}	*/
	}

	//alg4_1("../Chapter4/grammers/grammerA.txt", "here.txt");
}


void checkCommand(char* buf, char* ptr){


	if( strncmp( buf, ":help", 5) == 0 ){
		cout << "help entered" << endl;
	}


}
