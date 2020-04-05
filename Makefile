src_files  := $(wildcard src/*.c)
c_files  := $(wildcard *.c)

all:
	gcc $(c_files) ${src_files} -o main

clean:
	rm -f main