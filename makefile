### NOTE: the clang targets assume that clang is in your PATH -- make sure that is the case

all: 
	gcc -m32 -g -O -Wall struct.c main.c -o struct

clang:
	clang -m32 -g -O -Wall struct.c main.c -o struct

strict:
	gcc -m32 -g -O -Wall -Werror struct.c main.c -o struct

clang-strict:
	clang -m32 -g -fsanitize=undefined -O -Wall -Werror struct.c main.c -o struct

clean:
	rm -f struct
