move: move.c
	cc move.c -Wall -o move -O0

protect_lib: protect_lib.c
	cc -shared -fPIC -Wall protect_lib.c -o protect_lib.so -ldl

test_source:
	echo "123" > test_source.txt
	echo "123" > a.txt

test: move protect_lib test_source tests.sh protect_lib.so
	./tests.sh

clean:
	rm -f move *.txt *.so