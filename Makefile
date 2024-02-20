CC = cc
CFLAGS = -Wall -pedantic

<<<<<<< HEAD
SRCS = main.c labirynt.c
=======
SRCS = main.c generuj.c stos.c sciezka.c
>>>>>>> memory
OBJS = $(SRCS:.c=.o)

TARGET = main.out

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
