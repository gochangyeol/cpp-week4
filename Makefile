FLAGS= -Werror -std=c++11

main.exe: main.o 
	g++ -o main.exe main.o

main.o: main.cpp 
	g++ ${FLAGS} -c main.cpp



clean:
	rm -f *.o main.exe