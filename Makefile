src_files  := $(wildcard src/*.c)
c_files  := $(wildcard *.c)

all:
	gcc $(c_files) ${src_files} -o main

test:
	

clean:
	rm -f main