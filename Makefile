CC = gcc
CFLAGS = -Wall
DEPS = aesthetics.h
OBJ = main.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

calender-desktop: $(OBJ)
	gcc $(CFLAGS) -o $@ $^
