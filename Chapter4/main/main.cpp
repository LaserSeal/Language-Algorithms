#include "gramLib.h"
#include "gramIO.h"
#include "chap4.h"

using namespace std;
int main(){
	

	char gramIn[30] = "grammers/grammerA.txt";

	char gramOutA[30] = "grammer3.txt";
	char gramOutB[30] = "grammer3Out.txt";
	
	int i = 0;

//	char* test[10] = {"a", "aa", "aab", "baa", "aabb", "bbaa", "bbbaaa", "aaabbb", "abba", "bababa"};

	while(i++ < 1 ){
		alg4_8(gramOutA, gramOutB);//, test[i++]);
	}

/*
		alg4_1(gramOutA, gramOutB);
		alg4_2(gramOutB, gramOutA);
		alg4_3(gramOutA, gramOutB);
		alg4_4_2(gramOutB, gramOutA);
		alg4_4_4(gramOutA, gramOutB);*/
//		alg4_3(gramOutA, gramOutB);
//		alg4_4_2(gramOutA, gramOutB);
//		alg4_4_4(gramOutA, gramOutB);
//		*(gramOutA+10) += 1;
//		*(gramIn+16) += 1;
	//}

//		alg4_1("testGramer.txt", gramOutA);

//		alg4_2(gramOutA, gramOutB);
//		alg4_2(gramOutA, gramOutB);
//		alg4_2(gramOutA, gramOutB);
/*		*(gramOutA + 10) += 1;	
		alg4_3(gramOutB, gramOutA);
		*(gramOutB + 10) += 1;	
		alg4_4_2(gramOutA, gramOutB);
		*(gramOutA + 10) += 1;	
		alg4_4_4(gramOutB, gramOutA);	*/
	cout << gramOutA << endl;	
	cout << "WORKED" << endl;
	while(1);
}


