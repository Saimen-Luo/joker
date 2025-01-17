SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
CFLAGS = -Ilib -Wall

joker: $(OBJS)
	$(CC) $(CFLAGS) -o joker $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)
