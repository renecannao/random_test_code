

parser1.o: parser1.cpp
	g++ -c -o parser1.o parser1.cpp -ggdb -O2

c_tokenizer.o: c_tokenizer.c
	gcc -c -o c_tokenizer.o c_tokenizer.c -ggdb -O2

parser1: parser1.o c_tokenizer.o
	g++ parser1.o c_tokenizer.o -o parser1 -ggdb -O2
