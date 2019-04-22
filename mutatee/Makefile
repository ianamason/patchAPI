all: main liblib.so

main: main.c
	${CC} -o main main.c

liblib.so: lib.c
	${CC} -o liblib.so lib.c -shared -fPIC

main.txt: main
	objdump -S main > main.txt

newmain.txt: newmain
	objdump -S newmain > newmain.txt

clean:
	rm -rf main newmain *.txt *.so
