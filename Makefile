CC=g++
FLAGS= -std=c++11 -O3
DFLAGS= -std=c++11 -g -Wall

# optimized production target
fast: main.o calc.o Parser.o Tokenizer.o Condensor.o
	$(CC) $(FLAGS) main.o calc.o Parser.o Tokenizer.o Condensor.o -o fast
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c -o main.o
calc.o: calc.cpp calc.h
	$(CC) $(FLAGS) calc.cpp -c -o calc.o
Parser.o: Parser.cpp Parser.h  Tokenizer.h Function.h Condensor.h
		$(CC) $(FLAGS) Parser.cpp -c -o Parser.o
Tokenizer.o: Tokenizer.cpp Tokenizer.h
	$(CC) $(FLAGS) Tokenizer.cpp -c -o Tokenizer.o
Condensor.o: Condensor.cpp Condensor.h Parser.h
	$(CC) $(FLAGS) Condensor.cpp -c -o Condensor.o


# separate target for debugging
fastd: dmain.o dcalc.o dParser.o dTokenizer.o
		$(CC) $(DFLAGS) dmain.o dcalc.o dParser.o dTokenizer.o -o fastd
dmain.o: main.cpp
		$(CC) $(DFLAGS) main.cpp -c -o dmain.o
dcalc.o: calc.cpp calc.h
		$(CC) $(DFLAGS) calc.cpp -c -o dcalc.o
dParser.o: Parser.cpp Parser.h  Tokenizer.h Function.h
			$(CC) $(DFLAGS) Parser.cpp -c -o dParser.o
dTokenizer.o: Tokenizer.cpp Tokenizer.h
		$(CC) $(DFLAGS) Tokenizer.cpp -c -o dTokenizer.o

clean:
	rm *.o
