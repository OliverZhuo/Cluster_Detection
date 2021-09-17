FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

all: main.o spmat.o network_division.o linked_list.o groups.o group_division.o error_handle.o eigenpair.o maximization.o
	gcc $(FLAGS) main.o spmat.o network_division.o linked_list.o groups.o group_division.o error_handle.o eigenpair.o maximization.o -o cluster $(LIBS)
clean:
	rm -rf *.o cluster

main.o: main.c spmat.h error_handle.h network_division.h
	gcc $(FLAGS) -c main.c

spmat.o: spmat.c spmat.h error_handle.h
	gcc $(FLAGS) -c spmat.c

network_division.o: network_division.c spmat.h linked_list.h group_division.h error_handle.h maximization.h
	gcc $(FLAGS) -c network_division.c

linked_list.o: linked_list.c groups.h error_handle.h
	gcc $(FLAGS) -c linked_list.c

groups.o: groups.c error_handle.h
	gcc $(FLAGS) -c groups.c

group_division.o: group_division.c eigenpair.h network_division.h error_handle.h
	gcc $(FLAGS) -c group_division.c

error_handle.o: error_handle.c
	gcc $(FLAGS) -c error_handle.c

eigenpair.o: eigenpair.c spmat.h
	gcc $(FLAGS) -c eigenpair.c

maximization.o: maximization.c eigenpair.h group_division.h error_handle.h
	gcc $(FLAGS) -c maximization.c
