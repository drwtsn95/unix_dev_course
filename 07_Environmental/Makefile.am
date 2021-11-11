AM_FLAGS = -Wall -O0 -g
bin_PROGRAMS=rhasher
rhasher_SOURCES=rhasher.c

TESTS=tests.sh

test:
	chmod +x tests.sh
	./tests.sh

clean:
	git clean -df