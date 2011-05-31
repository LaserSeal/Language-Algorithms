#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include "library/lib.h"
#include "chap4.h"
#include "chap5_6.h"

#define BUF 80

void checkCommand(char* buf);

char welcome[] = "\
\t        _.-'''''-._\n\
\t      .'  _     _  '.\n\
\t     /   (o)   (o)   \\\n\
\t    |                 |\n\
\t    |  \\           /  |\n\
\t     \\  '.       .'  /\n\
\t      '.  `'---'`  .'\n\
\t        '-._____.-'\n\n\
\tWelcome, to the implemention of the Context Free and\n\
Finite State Automata algorithms. If your stuck type :h or :help\n\n\
The algorithms are based of formal lanauge algorithms from the book:\n\
Language and Machines by Thomas A. Sudkamp\n";

char helpComm[] = "\
:help - to display this\n\
:quit OR :q OR CTRL + D OR CRTL + C - to quit\n\
:ls <ARG> - to list the current files in dir\n\
:vim <FILE> - to edit a file using vim\n\
:cat <FILE> - displays a file\n\
----------------------------------------\n\
These are all the algorithms, anything in <ARGUMENT> brackets are the arguments\n\
alg4_1 <grammar pathIn> <grammer pathOut>\t--remove recurisve start symbol\t\t-Page 105\n\
alg4_2 <grammar pathIn> <grammer pathOut>\t--remove lamda rules\t\t\t-Page 108\n\
alg4_3 <grammar pathIn> <grammer pathOut>\t--remove chain rules\t\t\t-Page 114\n\
alg4_4_2 <grammar pathIn> <grammer pathOut>\t--generate rules that derive terminals\t-Page 117\n\
alg4_4_4 <grammar pathIn> <grammer pathOut>\t--remove un-reachable rules\t\t-Page 119\n\
alg4_5 <grammar pathIn> <grammer pathOut>\t--convert to Chomsky Normal Form\t-Page 122\n\
alg4_6 <grammar pathIn> <pdf pathOut> <string>\t--CYK algorithm\t\t\t\t-Page 126\n\
alg4_7 <grammar pathIn> <grammer pathOut>\t--removale of direct left recursion\t-Page 129\n\
alg4_8 <grammar pathIn> <grammer pathOut>\t--convert to Greibach Normal Form\t-Page 132\n\
alg5_6 <FA pathIn> <FA pathOut>\t\t\t--remove non-determinism\t\t-Page 172\n\
alg5_7 <FA pathIn> <FA pathOut>\t\t\t--determin equivalent states\t\t-Page 179\n\
alg6_2 <FA pathIn> <FA pathOut>\t\t\t--finite state to regular expression\t-Page 194\n";

using namespace std;
int main(){

	char* line;
	char buf[BUF];
	
	cout << welcome << endl;

	cout << ">> ";
	while( (fgets(buf, BUF, stdin)) != NULL ){
		checkCommand(buf);
		cout << ">> ";
	}

/*
	alg4_1("../Chapter4/grammers/grammerA.txt", "here.txt");
	alg4_2("../Chapter4/grammers/grammerA.txt", "here1.txt");
	alg4_3("../Chapter4/grammers/grammerA.txt", "here2.txt");
	alg4_4_2("../Chapter4/grammers/grammerA.txt", "here32.txt");
	alg4_4_4("../Chapter4/grammers/grammerA.txt", "here3.txt");
	alg4_5("../Chapter4/grammers/grammerA.txt", "here4.txt");
	alg4_6("../Chapter4/grammers/grammerA.txt", "here5.txt", "aabb");
	alg4_7("../Chapter4/grammers/grammerA.txt", "here6.txt");
	alg4_8("../Chapter4/grammers/grammerA.txt", "here7.txt");
	alg5_6("../Chapter5_6/alg5_6/dfa.txt", "here8.txt");
	alg5_7("../Chapter5_6/alg5_6/dfa.txt", "here9.txt");
	alg6_2("../Chapter5_6/alg5_6/dfa.txt", "here0.txt");
*/
}

void checkCommand(char* buf){

	char* ptr, *p, *tmp;
	char command[BUF];
	bool flag = true;
	vector<char*> splitCommand;
	
	ptr = strtok_r(buf, " ", &p);	

	while( ptr ){
		splitCommand.push_back(ptr);
		ptr = strtok_r(NULL, " \n", &p);	
	}
	

	if( strncmp( buf, ":help", 5) == 0 || strncmp(buf, ":h", 2) == 0){
		cout << helpComm << endl;
	}
	else if( strncmp( splitCommand[0], "alg", 3) == 0){
		ptr = (splitCommand[0]+3);
	
		if( splitCommand.size() >= 3 ){		
			if( strncmp(ptr, "4_1", 3) == 0 ){
				alg4_1(splitCommand[1], splitCommand[2]);
			}
			else if( strncmp(ptr, "4_2", 3) == 0 ){
				alg4_2(splitCommand[1], splitCommand[2]);
			}
			else if( strncmp(ptr, "4_3", 3) == 0 ){
				alg4_3(splitCommand[1], splitCommand[2]);
			}
			else if( strncmp(ptr, "4_4_2", 5) == 0 ){
				alg4_4_2(splitCommand[1], splitCommand[2]);
			}
			else if( strncmp(ptr, "4_4_4", 5) == 0 ){
				alg4_4_4(splitCommand[1], splitCommand[2]);
			}
			else if( strncmp(ptr, "4_5", 3) == 0 ){
				alg4_5(splitCommand[1], splitCommand[2]);
			}
			else if( strncmp(ptr, "4_6", 3) == 0 && splitCommand.size() == 4){
				alg4_6(splitCommand[1], splitCommand[2], splitCommand[3]);
			}
			else if( strncmp(ptr, "4_7", 3) == 0 ){
				alg4_7(splitCommand[1], splitCommand[2]);
			}
			else if( strncmp(ptr, "4_8", 3) == 0 ){
				alg4_8(splitCommand[1], splitCommand[2]);
			}
			else if( strncmp(ptr, "5_6", 3) == 0 ){
				alg5_6(splitCommand[1], splitCommand[2]);
			}
			else if( strncmp(ptr, "5_7", 3) == 0 ){
				alg5_7(splitCommand[1], splitCommand[2]);
			}
			else if( strncmp(ptr, "6_2", 3) == 0 ){
				alg6_2(splitCommand[1], splitCommand[2]);
			}
			else{
				cout << splitCommand[0] << " is not an algorithm or you gave incorrect params, please type :help to see the list" << endl;
				flag = false;
			}
		
			if( splitCommand.size() == 3 && flag){	
				cout << endl;
				printTextFile(splitCommand[2]);
			}
			else if( splitCommand.size() == 4 && flag){
				cout << "A pdf has been produced called: " << splitCommand[2] << ".pdf" << endl;
			}
		}
		else{
			cout << "To few arguments to run an algorithm, please type :h OR :help to get the arguments" << endl;
		}	
	
	}
	else if( strncmp( buf, ":quit", 5) == 0 || strncmp( buf, ":q", 2) == 0 ){
		cout << "haha you want to quit" << endl;
		exit(1);
	}
	else if( strncmp( buf, ":ls", 3) == 0){
		strncpy( command, "ls --hide=*.o ", 15);		
		if( splitCommand.size() == 2){
			strcat(command, splitCommand[1]);
		}
		system(command);
	}
	else if( strncmp( buf, ":vim", 4) == 0 && splitCommand.size() == 2){
		strncpy(command, "vim ", 5);
		strcat(command, splitCommand[1]);
		system(command);
	}
	else if( strncmp( buf, ":cat", 4) == 0 && splitCommand.size() == 2){
		strncpy(command, "cat ", 5);
		strcat(command, splitCommand[1]);
		cout << endl;
		system(command);
		cout << endl;
	}
	else{
		cout << "command not recognize, enter :h OR :help if your lost"  << endl;
	}

}
