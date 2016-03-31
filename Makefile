all: Sudoku.o giveQuestion.o solve.cpp transform.cpp
	g++ -o giveQuestion  Sudoku.o giveQuestion.o
	g++ -o solve solve.cpp Sudoku.o
	g++ -o transform transform.cpp Sudoku.o

Sudoku.o: Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp

giveQuestion.o: giveQuestion.cpp
	g++ -c giveQuestion.cpp

clean:
	rm  *o
