OBJS = $(MAIN).o alg5_6.o alg5_7.o alg6_2.o lib.o finLib.o finiteStateIO.o
MAIN = main

all: clean compile

compile: $(OBJS)
	g++ $(OBJS) -o test 

$(MAIN).o:
	g++ -c $(MAIN).cpp
	
alg5_6.o:
	g++ -c ../alg5_6/alg5_6.cpp

alg5_7.o:
	g++ -c ../alg5_7/alg5_7.cpp

alg6_2.o:
	g++ -c ../alg6_2/alg6_2.cpp

lib.o:
	g++ -c ../../Main/library/lib.cpp

finLib.o:
	g++ -c ../library/finLib.cpp

finiteStateIO.o:
	g++ -c ../library/finiteStateIO.cpp

remove:
	rm $(MAIN).o

clean:
	rm -rf *o compile
