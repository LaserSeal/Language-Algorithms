#include <iostream>
#include <set>
#include <vector>
#include <string.h>

template <class T>
void freeCont(T& cont);

void test();
using namespace std;
int main(){
	
	int i = 0;

	while( i++ < 1){
		test();
	}


	while(1);
	//freeCont(test);

}


void test(){

	cout << "test" << endl;
	vector<char*> test;
	char* tmp;
/*
	for( int i = 0; i < 10; i++){
		tmp = new char[10];
		strncpy(tmp, "hello", 6);
		*(tmp+6) = ((char)i)+1;
		*(tmp+7) = '\0';
		test.push_back(tmp);
	}
	
*/
}

template <class T>
void freeCont(T& cont){

	typename T::iterator it;
	
	//cont.~T();
	
	// Could use ++it, but not defined for all STL Containers
	for( it = cont.begin(); it != cont.end(); it++){
		delete(*it);				
	}
}
