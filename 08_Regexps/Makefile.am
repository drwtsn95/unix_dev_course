AM_FLAGS = -WALL -O0 -g
bin_PROGRAMS=esub
esub_SOURCES=esub.c

TESTS=tests.sh

test:
	chmod +x tests.sh
	./tests.sh

clean:
	git clean -df