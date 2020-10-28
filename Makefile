final.elf: 1.o 2.o
	gcc 1.o 2.o -o final.elf

2.o: 2.c myProject.h
	gcc 2.c -c -o 2.o 

1.o: 1.c myProject.h
	gcc 1.c -c -o 1.o
