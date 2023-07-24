CC = gcc

CFLAGS = -Wall -Wextra -Wformat -L/usr/lib/x86_64-linux-gnu

TARGET = exp
SOURCES = main.c

all: $(TARGET)

$(TARGET):main.o
	$(CC) $(CFLAGS) $? -o $(TARGET)

main.o: $(SOURCES)
	$(CC) $(CFLAGS) -c $? -o $@

clean:
	rm -rf *.o $(TARGET)