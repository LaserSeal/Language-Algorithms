#include <stdio.h>
#include <iostream>
#include <string.h>
#include "chap4.h"
#include "chap5_6.h"

void checkCommand(char* buf, char* ptr);

using namespace std;
int main(){

	char* line;
	char* p;
	char buf[80];

	while( (fgets(buf, 80, stdin)) != NULL ){
		line = strtok_r(buf, " ", &p);
		checkCommand(line, p);
		/*
		while(line){
		line = strtok_r(NULL, " \n", &p);
		} */
	}


	alg4_1("../Chapter4/grammers/grammerA.txt", "here.txt");
	alg4_2("../Chapter4/grammers/grammerA.txt", "here1.txt");
	alg4_3("../Chapter4/grammers/grammerA.txt", "here2.txt");
	alg4_4_2("../Chapter4/grammers/grammerA.txt", "here3.txt");
	alg4_5("../Chapter4/grammers/grammerA.txt", "here4.txt");
	alg4_6("../Chapter4/grammers/grammerA.txt", "here5.txt", "aabb");
	alg4_7("../Chapter4/grammers/grammerA.txt", "here6.txt");
	alg4_8("../Chapter4/grammers/grammerA.txt", "here7.txt");
}

void checkCommand(char* buf, char* p){

	char* ptr;

	if( strncmp( buf, ":help", 5) == 0 ){
		cout << "help entered" << endl;
	}
	else if( strncmp( buf, ":alg", 4) == 0 ){
		ptr = (buf+4);
		cout << ptr << endl;

	}
	else if( strncmp( buf, ":quit", 5) == 0 || strncmp( buf, ":q", 2) == 0 ){
		cout << "haha you want to quit" << endl;
	}
	else{
		cout << "here" << endl;
	}

}



























