FLAGS = -O3
CC = gcc
serial: serial.o mmio.o my_csc.o my_scc.o Makefile
	$(CC) $(FLAGS) serial.o mmio.o my_csc.o my_scc.o -o serial

serial.o: serial.c Makefile
	$(CC) $(FLAGS) -c serial.c -Ilib/

mmio.o: lib/mmio.c lib/mmio.h Makefile
	$(CC) $(FLAGS) -c lib/mmio.c

my_csc.o: lib/my_csc.c lib/my_csc.h Makefile
	$(CC) $(FLAGS) -c lib/my_csc.c

my_scc.o: lib/my_scc.c lib/my_scc.h Makefile
	$(CC) $(FLAGS) -c lib/my_scc.c

clean:
	rm *.o serial