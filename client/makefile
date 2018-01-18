a.out: compileAll
	g++ *.o -o client
	rm -f *.o

compileAll: include/*.h src/*.cpp
	g++ -Iinclude/ -c src/*.cpp

run:
	./a.out
