OBJS = alg4_1.o lib.o grammerIO.o
MAIN = alg4_1

all: remove compile

new: compile

compile: $(OBJS)
	g++ $(OBJS) -o test 

$(MAIN).o:
	g++ -c $(MAIN).cpp
	
lib.o:
	g++ -c ../library/lib.cpp

grammerIO.o:
	g++ -c ../library/grammerIO.cpp

remove:
	rm $(MAIN).o

clean:
	rm -rf *o compile
