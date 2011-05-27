#include "chap5_6.h"
#include "finLib.h"
#include "finStateIO.h"

using namespace std;
int main(){

	int i = 0;
	while(i++ < 1000){
		alg6_2("dfa2.txt", "here.txt");
	}
	cout << "--END--" << endl;

        // To Test for mem leaks.
	while(1);

}
