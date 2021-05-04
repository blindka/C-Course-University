myText:	myText.o
	gcc -g -ansi -Wall -pedantic myText.o -o myText -lm
myText.o: myText.c
	gcc -c -ansi -Wall -pedantic myText.c -o myText.o -lm
