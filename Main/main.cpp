#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "chap4.h"
#include "chap5_6.h"

#define BUF 80

void checkCommand(char* buf);

char* builtInGrammer[10] = {"S -> as | AB | AC\nA -> aA | $\nB -> bS | bB\nC -> cC | $"};
char helpComm[] = "\
:help - to display this\n\
:quit OR :q - quit\n\
:alg4_1 <grammar pathIn> <grammer pathOut>\t--remove recurisve start symbol\n\
:alg4_2 <grammar pathIn> <grammer pathOut>\t--remove lamda rules\n\
:alg4_3 <grammar pathIn> <grammer pathOut>\t--remove chain rules\n\
:alg4_4_2 <grammar pathIn> <grammer pathOut>\t--generate rules that derive terminals\n\
:alg4_4_4 <grammar pathIn> <grammer pathOut>\t--remove un-reachable rules\n\
:alg4_5 <grammar pathIn> <grammer pathOut>\t--convert to Chomsky Normal Form\n\
:alg4_6 <grammar pathIn> <pdf pathOut> <string>\t--CYK algorithm\n\
:alg4_7 <grammar pathIn> <grammer pathOut>\t--removale of direct left recursion\n\
:alg4_8 <grammar pathIn> <grammer pathOut>\t--convert to Greibach Normal Form\n\
:alg5_6 <FA pathIn> <FA pathOut>\t\t--remove non-determinism\n\
:alg5_7 <FA pathIn> <FA pathOut>\t\t--determin equivalent states\n\
:alg6_2 <FA pathIn> <FA pathOut>\t\t--finite state to regular expression\n";

using namespace std;
int main(){

	char* line;
	char buf[BUF];

	alg4_1("gram.txt", "gramOut.txt");

	while( (fgets(buf, BUF, stdin)) != NULL ){
		//line = strtok_r(buf, " ", &p);
		checkCommand(buf);
		/*
		while(line){
		line = strtok_r(NULL, " \n", &p);
		} */
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
	vector<char*> splitCommand;
	
	ptr = strtok_r(buf, " ", &p);	


	while( ptr ){
		splitCommand.push_back(ptr);
		ptr = strtok_r(NULL, " \n", &p);	
	}
	

	if( strncmp( buf, ":help", 5) == 0 || strncmp(buf, ":h", 2) == 0){
		cout << helpComm << endl;
	}
	else if( strncmp( splitCommand[0], ":alg", 4) == 0){
		ptr = (splitCommand[0]+4);
	
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
				cout << splitCommand[0] << " is not an algorithm or you have bad param, please type :help to see the list" << endl; 
			}
		}
		else{
			cout << "To few arguments to run an algorithm, please type :h OR :help to get the arguments" << endl;
		}	
	
	}
	else if( strncmp( buf, ":quit", 5) == 0 || strncmp( buf, ":q", 2) == 0 ){
		cout << "haha you want to quit" << endl;
	}
	else{
		cout << "command not recognize, enter :h OR :help if your lost"  << endl;
	}

}
