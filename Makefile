final.elf: 1.o 2.o main.c
	gcc main.c -l inout -L -o final.elf

libinout.so: 1.o 2.o
	gcc -o libinout.so -shared -fPIC 1.o 2.o
	
2.o: 2.c myProject.h
	gcc -o 2.o -shared -fPIC -c 2.c 

1.o: 1.c myProject.h
	gcc -o 1.o -shared -fPIC -c 1.c
