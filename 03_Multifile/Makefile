override CFLAGS+= -fPIC
%.o: %.c
	cc  $< -fPIC -c -o $@
all: const.o fun.o prog.o prog liboutput_static.a liboutput.so prog-a prog-so
prog: const.o fun.o prog.o
	cc  $^ -o $@
liboutput_static.a: const.o fun.o
	ar -rcs liboutput_static.a const.o fun.o
liboutput.so: const.o fun.o
	cc -shared const.o fun.o -o liboutput.so
prog-a: prog.o liboutput_static.a
	cc -L. prog.o liboutput_static.a -o prog-a
prog-so: prog.o liboutput.so
	cc prog.o liboutput.so -o prog-so
clean:
	rm -f prog *.o liboutput_static.a liboutput.so prog-a prog-so
