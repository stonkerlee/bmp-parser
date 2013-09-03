main: 24bit-bmp-parser.o
	gcc -o main $^

clean:
	rm -f *.o main
