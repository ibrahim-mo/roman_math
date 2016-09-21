#SUBDIRS = src . tests

all:
	(cd ./src && make)

check:
	(cd ./tests && make check)

clean:
	(cd ./src && make clean)
	(cd ./tests && make clean)
