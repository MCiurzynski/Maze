CC = cc
CFLAGS = -Wall -pedantic

SRCS = main.c generuj.c stos.c sciezka.c
OBJS = $(SRCS:.c=.o)

TARGET = main.out

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
