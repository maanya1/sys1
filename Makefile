src_files  := $(wildcard src/*.c)
c_files := $(wildcard *.c)

all:
	gcc -g $(c_files) $(src_files) -o fileCompressor

# Tests build codebook, compression, decompression
test_program: all
	./fileCompressor -b -R ./examples
	./fileCompressor -c -R ./examples ./HuffmanCodes
	./fileCompressor -d -R ./examples ./HuffmanCodes

clean:
	rm -f fileCompressor HuffmanCodes
	find . -type f -name "*.hcz" -delete