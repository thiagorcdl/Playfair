all:
	gcc -o cript src/cript.c
	gcc -o decript src/decript.c

clean:
	rm -f *.o *~ out/* parcial/* *.cript cript decript
