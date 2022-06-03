all: main.exe
	echo "it is completed"

main.exe: intarray.o tools.o main.o jstl.o stringarray.o
	gcc intarray.o tools.o main.o jstl.o stringarray.o -o main.exe

main.o: main.c intarray.h tools.h
	gcc -c main.c

intarray.o: intarray.c intarray.h tools.h
	gcc -c intarray.c

tools.o: tools.c tools.h
	gcc -c tools.c

jstl.o: jstl.c jstl.h tools.h intarray.h
	gcc -c jstl.c

stringarray.o: stringarray.c jstl.h tools.h intarray.h
	gcc -c stringarray.c

