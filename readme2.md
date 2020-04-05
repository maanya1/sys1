# Read Me

## Time Space Complexity Analysis

_Include an analysis of the time and space usage and complexity of your program. You do not
need to analyze every size function, but you should analyze the overall program's time and
space used as a function of the size of the input._

### Tokenizing the file
This project is intended to be used as a file compression system. In the terminal we are 
given a 2 flags (whether to build the huffman codebook recursively or not), and then a path or a file. 
We tokenize the file in tokens.c by using whitespaces as a delimiter. Tokens.c has 2 functions: Token_create and Token_create_frequency which assigned the word and the frequency to a token. Token_read_file reads the file in general, but token_read_file_distinct read the file and incremented the frequencies. All the tokens were stored in a linked list.

### Build Codebook

- Count Frequency
- Create Huffman Tree: We created the equivalent of a heap class with functions that created nodes for the heap, inserted nodes into the heap, sifted an element up to its proper place, removed the minimum, etc. The heap was used to build the huffman codebook. This was done by heapifying the tokens from the linked list, and then removing and merging the two smallest elements of the minheap and inserting it back in. Ultimately we are left with a tree which results in the codebook.
- Print Huffman Tree

#### Count Freqeuncy
We created a function called `Token_read_file_distinct` which read a file into a linked list containing words, delimeters and their respective frequencies.

1. First, it read all of the words and delimeters into a linked list.

> Each linked list insertion is O(_1_) and we do _n_ of these. **The runtime of this operation is O(_n_)**.

2. Next, it removed all of the duplicates by inserting every linked list item into a new list only if it was not containined in the list.

> Each linked list insertion for a distinct linked list is O(_n_) and we do _n_ of these. **The runtime of this operation is O(_n<sup>2</sup>_)**.

The total run time is: **_n_ + _n<sup>2</sup>_ =  O(_n<sup>2</sup>_)**.

### Compression

### Decompression


 
