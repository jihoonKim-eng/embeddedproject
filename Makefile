final.elf: 1.o 2.o main.c
	gcc 1.o 2.o main.c -o final.elf
	
2.o: 2.c myProject.h
	gcc -o 2.o -c 2.c 

1.o: 1.c myProject.h
	gcc -o 1.o -c 1.c
