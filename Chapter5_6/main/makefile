OBJS = $(MAIN).o alg5_6.o lib.o finiteStateIO.o
MAIN = main

all: remove compile

new: compile

compile: $(OBJS)
	g++ $(OBJS) -o test 

$(MAIN).o:
	g++ -c $(MAIN).cpp
	
alg5_6.o:
	g++ -c ../alg5_6/alg5_6.cpp

lib.o:
	g++ -c ../library/lib.cpp

finiteStateIO.o:
	g++ -c ../library/finiteStateIO.cpp

remove:
	rm $(MAIN).o

clean:
	rm -rf *o compile
