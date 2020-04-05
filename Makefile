src_files  := $(wildcard src/*.c)
c_files := $(wildcard *.c)

all:
	gcc -g $(c_files) $(src_files) -o main

clean:
	rm -f main
	find . -type f -name "*.hez" -delete