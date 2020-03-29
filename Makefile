c_files  := $(wildcard *.c)

all:
	gcc $(c_files) -o main

clean:
	rm -f main