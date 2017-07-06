CC = clang++ 
FLAGS = -g -std=c++11  

all: searcher

searcher: main.o boolean.o vectorModel.o pageRank.o anchorRank.o searcher.o
	g++ main.o boolean.o vectorModel.o pageRank.o anchorRank.o searcher.o $(FLAGS) -o searcher

main.o: main.cpp 
	g++ $(FLAGS) -c main.cpp

boolean.o: boolean.h boolean.cpp 
	g++ $(FLAGS) -c boolean.cpp

vectorModel.o: vectorModel.h vectorModel.cpp 
	g++ $(FLAGS) -c vectorModel.cpp	

pageRank.o: pageRank.h pageRank.cpp 
	g++ $(FLAGS) -c pageRank.cpp	

anchorRank.o: anchorRank.h anchorRank.cpp 
	g++ $(FLAGS) -c anchorRank.cpp

searcher.o: searcher.h searcher.cpp 
	g++ $(FLAGS) -c searcher.cpp

clean:
	rm *.o searcher
