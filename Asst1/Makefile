src_files := $(wildcard src/*.c)
c_files := $(wildcard *.c)

all:
	gcc $(c_files) $(src_files) -o fileCompressor

clean:
	rm -f fileCompressor HuffmanCodebook
	find ./tests/ -type f -name "*.hcz" -delete

test_build: all
	./fileCompressor -R -b ./tests

test_compress: test_build
	./fileCompressor -R -c ./tests ./HuffmanCodebook
	find ./tests/ -type f ! -name "*.hcz" -delete

test_decompress: test_compress
	./fileCompressor -R -d ./tests ./HuffmanCodebook

pdf:
	pandoc README.md -o README.pdf