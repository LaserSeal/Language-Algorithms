#include "chap5_6.h"
#include "lib.h"
#include "finStateIO.h"

using namespace std;
int main(){

	int i = 0;
	while(i++ < 50){
		alg5_6("../alg5_6/dfa3.txt", "here.txt");
	}
	cout << "--END--" << endl;

	while(1);

}
