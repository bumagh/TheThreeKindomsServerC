CC = gcc 
SRCS = $(wildcard *.c)
BINS = $(patsubst %.c, %, $(SRCS))
LIBS = -lsqlite3
WFLAGS = -pedantic-errors -Wall -Wextra
.PHONY: clean

all: $(BINS)

%: %.c
	$(CC) $(WFLAGS) -o $@ $<  $(LIBS) 

clean: 
	rm -f $(BINS)