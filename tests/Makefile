CC=gcc
CFLAGS=-c -Wall -Werror -fpic -I../src -I/usr/local/include
LDFLAGS=-Wl,-rpath=../src,-rpath=/usr/local/lib -L../src -L/usr/local/lib
#CFLAGS=-c -Wall -Werror -fpic -I../src -I/usr/include
#LDFLAGS=-Wl,-rpath=../src,-rpath=/usr/lib -L../src -L/usr/lib
SOURCES=check_roman_math.c
OBJECTS=$(SOURCES:.c=.o)
EXEC=check_roman_math

check: $(EXEC)
	./check_roman_math

$(EXEC): check_roman_math.o
	$(CC) $< $(LDFLAGS) -lroman_math -lcheck -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXEC)
