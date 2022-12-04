FLAGS = -O3 -fopenmp
CC = gcc
open-mp: open-mp.o mmio.o my_csc.o my_scc.o Makefile
	$(CC) $(FLAGS) open-mp.o mmio.o my_csc.o my_scc.o -o open-mp

open-mp.o: open-mp.c Makefile
	$(CC) $(FLAGS) -c open-mp.c -Ilib/

mmio.o: lib/mmio.c lib/mmio.h Makefile
	$(CC) $(FLAGS) -c lib/mmio.c

my_csc.o: lib/my_csc.c lib/my_csc.h Makefile
	$(CC) $(FLAGS) -c lib/my_csc.c

my_scc.o: lib/my_scc.c lib/my_scc.h Makefile
	$(CC) $(FLAGS) -c lib/my_scc.c

clean:
	rm *.o open-mp