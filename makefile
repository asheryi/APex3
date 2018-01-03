a.out: compileAll
	g++ *.o
	rm -f *.o

compileAll: include/*.h src/*.cpp
	g++ -pthread -Iinclude/ -c src/*.cpp

run:
	./a.out
