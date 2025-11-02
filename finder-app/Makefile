ifneq ($(CROSS_COMPILE),)
  CC = $(CROSS_COMPILE)gcc
else
  CC = gcc
endif

all: writer

clean:
	rm -f writer *.o

writer: writer.o
	$(CC) $^ -o $@

writer.o:
	$(CC) writer.c -Wall -g -c -o $@

