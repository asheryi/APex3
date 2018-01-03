a.out: compileAll
	g++ -pthread *.o
	rm -f *.o

compileAll: include/*.h src/*.cpp
	g++ -Iinclude/ -c src/*.cpp

run:
	./a.out
