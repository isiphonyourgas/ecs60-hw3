ExtendibleMain.out: ExtendibleMain.cpp ExtendibleHash.cpp ExtendibleHash.h
	g++ -Wall -ansi -g -o ExtendibleMain.out ExtendibleMain.cpp
clean:
	rm -f ExtendibleMain.out results*.txt
