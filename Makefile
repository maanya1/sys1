src_files  := $(wildcard src/*.c)
c_files := $(wildcard *.c)

all:
	gcc -g $(c_files) $(src_files) -o main

test: all
	./main -b -R ./examples
	./main -c -R ./examples ./HuffmanCodes
	find . -type f -name "*.hcz" -delete
	./main -d -R ./examples ./HuffmanCodes

clean:
	rm -f main