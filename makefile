make: functions.c store.c
	gcc -c functions.c
	gcc store.c functions.o
