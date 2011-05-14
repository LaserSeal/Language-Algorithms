#include "lib.h"
#include "gramIO.h"
#include "stdlib.h"
#include "latex.h"

using namespace std;

void outputLatex( vector<vector<set<char*> > > matrix, char* pathOut, int size){


	char final[MAX_FILE_SIZE*2] = "";
	char topHalf[MAX_FILE_SIZE*2] = "\\documentclass{article}\n\n\\usepackage[english]{babel}\n\n\\begin{document}\n\n\\begin{center}\n\t\\begin{tabular}{";// | l | l | l | l |}\n\t\\hline\n\t";
	char botHalf[] = "\t\\hline\n\t\\end{tabular}\n\\end{center}\n\n\\end{document}\n";
	char pdflatex[256] = "pdflatex ";
	set<char*>::iterator it;
	
	strncat(topHalf, " |", 2);
	for( int i = 0; i < size; i++){
		strncat(topHalf, " c |", 4);
	}

	strncat(topHalf, "}\n\t\\hline\n\t", 12);

	for( int i = 1; i <= size; i++){
		for( int j = 1; j <= size; j++){
			if( j < i ) {
				strncat(topHalf, "-", 1);
			}
			else{
				strncat(topHalf, "\\{", 2);
				for( it = matrix[i][j].begin(); it != matrix[i][j].end();){	
					strncat(topHalf, *it, MAX_VAR_SIZE);
					if( (++it) != (matrix[i][j].end())){
						strncat(topHalf, ", ", 1);
					}
				}

				strncat(topHalf, "\\}", 2);
			}
		
			if( (j+1) <= size ){
				strncat(topHalf, " & ", 4);
			}
	
		}
		
		strncat(topHalf, " \\\\ \\hline\n\t", 12); 

	}	


	strcat(final, topHalf);
	strcat(final, botHalf);
	sendStream(pathOut, final);
	strcat(pdflatex, pathOut);
	strcat(pdflatex, " >/dev/null");
	system(pdflatex);
	

/*	system("rm tmp.log");
	system("rm tmp.tex");
	system("rm tmp.aux");	*/



}
