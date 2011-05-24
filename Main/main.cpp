
#include <stdio.h>
#include <iostream>
//#include "chap4.h"
#include "chap5_6.h"

using namespace std;
int main(){

	char* line;
	char buf[80];

	while( (fgets(buf, 80, stdin)) != NULL ){
		cout << buf << endl;
	}

	//alg4_1("../Chapter4/grammers/grammerA.txt", "here.txt");
}
