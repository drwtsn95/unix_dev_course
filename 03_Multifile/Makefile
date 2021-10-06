CFLAGS = -fPIC
GENERATES = prog prog-a prog-so test
TRASH = *.o *~ o.* *.a *.so *.res *.err
PAR1 = 2
PAR3 = 3 4 5
RES1 = 1.res
RES2 = 2.res
RES3 = 3.res
ERR1 = 1.err
ERR2 = 2.err
ERR3 = 3.err

all:    test prog

prog:   const.o fun.o prog.o
		$(CC) $^ -o $@

fun.o:  outlib.h

liboutput_static.a: fun.o const.o
		ar -rcs $@ $^

prog-a: prog.o liboutput_static.a
		$(CC) -L. $< -loutput_static -o $@

liboutput.so:  fun.o const.o
	$(CC) -shared $^ -o $@

prog-so: prog.o liboutput.so
	$(CC) -L. $< -loutput -o $@

tprog: prog
		./$^ 2> $(ERR1) 1> $(RES1)
		./$^ 2>> $(ERR1) 1>> $(RES1) $(PAR1)
		./$^ 2>> $(ERR1) 1>> $(RES1) $(PAR3)

tprog-a: prog-a
		./$^ 2> $(ERR2) 1> $(RES2)
		./$^ 2>> $(ERR2) 1>> $(RES2) $(PAR1)
		./$^ 2>> $(ERR2) 1>> $(RES2) $(PAR3)

tprog-so: prog-so
		LD_LIBRARY_PATH=`pwd` ./$^ 2> $(ERR3) 1> $(RES3)
		LD_LIBRARY_PATH=`pwd` ./$^ 2>> $(ERR3) 1>> $(RES3) $(PAR1)
		LD_LIBRARY_PATH=`pwd` ./$^ 2>> $(ERR3) 1>> $(RES3) $(PAR3)

test: tprog tprog-a tprog-so
		cmp $(RES1) $(RES2)
		cmp $(RES1) $(RES3)
		cmp $(RES2) $(RES3)
		cmp $(ERR1) $(ERR2)
		cmp $(ERR1) $(ERR3)
		cmp $(ERR2) $(ERR3)

clean:
		rm -f $(TRASH)

distclean:      clean
		rm -rf $(GENERATES)
