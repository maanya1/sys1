src_files := $(wildcard src/*.c)
c_files := $(wildcard *.c)

all:
	gcc -g $(c_files) $(src_files) -o fileCompressor

clean:
	rm -f fileCompressor HuffmanCodes
	find . -type f -name "*.hcz" -delete

pdf:
	pandoc README.md -o README.pdf

test_build: all
	./fileCompressor -R -b ./tests

test_compress: test_build
	./fileCompressor -R -c ./tests ./HuffmanCodes

test_decompress: test_compress
	./fileCompressor -R -d ./tests ./HuffmanCodes

test_all: test_decompress