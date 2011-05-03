#include "lib.h"
#include "gramIO.h"
#include "chap4.h"

using namespace std;
int main(){
	

	char gramIn[30] = "grammers/grammerA.txt";

	char gramOutA[30] = "grammerA.txt";
	char gramOutB[30] = "grammerB.txt";
	
	int i = 0;

	while(i++ < 10){
		alg4_6(gramOutA, gramOutB, "aaba");
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

}


