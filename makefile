neuralNetwork: bin bin/main.exe

bin/: 
	mkdir bin

bin/main.exe: bin/main.o bin/ParseArgs.o	
	gcc bin/main.o bin/ParseArgs.o -o bin/main.exe 

bin/main.o: driver/main.c
	gcc -c driver/main.c 
	mv main.o bin/ 

bin/ParseArgs.o: misc/ParseArgs.c
	gcc -c misc/ParseArgs.c
	mv ParseArgs.o bin/

clean:
	rm -rf bin
	rm -rf *.txt


