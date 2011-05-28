OBJS = $(MAIN).o alg4_1.o alg4_2.o alg4_3.o alg4_4_2.o alg4_4_4.o alg4_5.o alg4_6.o alg4_7.o alg4_8.o latexTable.o gramLib.o grammerIO.o alg5_6.o alg5_7.o alg6_2.o lib.o finLib.o finiteStateIO.o
MAIN = main
NAME = shell

all: clean compile

again: rmMain $(MAIN).o reMake

compile: $(OBJS)
	g++ $(OBJS) -o $(NAME)

reMake:
	g++ *.o -o $(NAME)

$(MAIN).o:
	g++ -c $(MAIN).cpp
	
alg4_1.o:
	g++ -c ../Chapter4/alg4_1/alg4_1.cpp

alg4_2.o:
	g++ -c ../Chapter4/alg4_2/alg4_2.cpp

alg4_3.o:
	g++ -c ../Chapter4/alg4_3/alg4_3.cpp

alg4_4_2.o:
	g++ -c ../Chapter4/alg4_4/4_4_2/alg4_4_2.cpp

alg4_4_4.o:
	g++ -c ../Chapter4/alg4_4/4_4_4/alg4_4_4.cpp

alg4_5.o:
	g++ -c ../Chapter4/alg4_5/alg4_5.cpp

alg4_6.o:
	g++ -c ../Chapter4/alg4_6/alg4_6.cpp

alg4_7.o:
	g++ -c ../Chapter4/alg4_7/alg4_7.cpp

alg4_8.o:
	g++ -c ../Chapter4/alg4_8/alg4_8.cpp

latexTable.o:
	g++ -c ../Chapter4/alg4_6/latexTable.cpp

gramLib.o:
	g++ -c ../Chapter4/library/gramLib.cpp

grammerIO.o:
	g++ -c ../Chapter4/library/grammerIO.cpp

alg5_6.o:
	g++ -c ../Chapter5_6/alg5_6/alg5_6.cpp

alg5_7.o:
	g++ -c ../Chapter5_6/alg5_7/alg5_7.cpp

alg6_2.o:
	g++ -c ../Chapter5_6/alg6_2/alg6_2.cpp

lib.o:
	g++ -c library/lib.cpp

finLib.o:
	g++ -c ../Chapter5_6/library/finLib.cpp

finiteStateIO.o:
	g++ -c ../Chapter5_6/library/finiteStateIO.cpp

clean:
	rm -rf *o

rmMain:
	rm -rf $(MAIN).o
