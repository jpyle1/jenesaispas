neuralNetwork: bin bin/main.exe

bin/: 
	mkdir bin

bin/main.exe: bin/main.o bin/ParseArgs.o bin/Generate.o	bin/Neural.o
	gcc bin/Neural.o bin/main.o bin/ParseArgs.o bin/Generate.o -o bin/main.exe 

bin/main.o: driver/main.c
	gcc -c driver/main.c 
	mv main.o bin/ 

bin/ParseArgs.o: misc/ParseArgs.c ParseArgs.h
	gcc -c misc/ParseArgs.c
	mv ParseArgs.o bin/

bin/Generate.o: misc/Generate.c Generate.h
	gcc -c misc/Generate.c
	mv Generate.o bin/

bin/Neural.o: neural/Neural.c Neural.h
	gcc -c neural/Neural.c
	mv Neural.o bin/	

clean:
	rm -rf bin
	rm -rf *.txt


