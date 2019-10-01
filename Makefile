all: Proj1Test.o SquareList.o InnerSquareList.o
	g++ -Wall -std=c++11 Proj1Test.o SquareList.o InnerSquareList.o -o output

SquareList.o : SquareList.cpp SquareList.h
	g++ -Wall -std=c++11 -c SquareList.cpp

InnerSquareList.o : InnerSquareList.cpp InnerSquareList.h
	g++ -Wall -std=c++11 -c InnerSquareList.cpp

Proj1Test.o: Proj1Test.cpp
	g++ -Wall -std=c++11 -c Proj1Test.cpp

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

run:
	./output