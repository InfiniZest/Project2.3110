objects = snakePre.o console.o

snakeProject : $(objects)
	g++ -o snakeProject $(objects) -lncurses

Console.o : console.cpp console.h snake_c.cpp
	g++ -c Console.cpp

snakeProject.o : snakePre.cpp console.h
	g++ -c snakeProject.cpp

clean:
	rm snakeProject $(objects)
