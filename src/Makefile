CC=gcc
CFLAGS=-c -Wall -Werror -fpic -I../src
LDFLAGS=-Wl,-rpath=../src -L../src
SOURCES=roman_math.c main.c
OBJECTS=$(SOURCES:.c=.o)
SHARED_LIB=roman_math
EXEC=main

all: $(SHARED_LIB) $(EXEC)

$(EXEC): main.o $(SHARED_LIB)
	$(CC) $< $(LDFLAGS) -l$(SHARED_LIB) -o $@

$(SHARED_LIB): roman_math.o
	$(CC) -shared -o lib$(SHARED_LIB).so $<
	#ar rcs lib$(SHARED_LIB).a $<

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) lib$(SHARED_LIB).* $(EXEC)
