#include "chap5_6.h"
#include "lib.h"
#include "finStateIO.h"

using namespace std;
int main(){

	int i = 0;
	while(i++ < 1000){
		alg5_7("dfa.txt", "here.txt");
	}
	cout << "--END--" << endl;


	while(1);

}
