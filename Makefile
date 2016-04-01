all: Sudoku.o giveQuestion.o solve.cpp transform.cpp
	g++ -g -o giveQuestion  Sudoku.o giveQuestion.o
	g++ -g -o solve solve.cpp Sudoku.o
	g++ -g -o transform transform.cpp Sudoku.o

Sudoku.o: Sudoku.cpp Sudoku.h
	g++ -g -c Sudoku.cpp

giveQuestion.o: giveQuestion.cpp
	g++ -g -c giveQuestion.cpp

clean:
	rm  *o
