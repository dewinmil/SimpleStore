make: functions.c store.c
	gcc -c functions.c -lm
	gcc store.c functions.o -lm
