CC=cc
CFLAGS=-O0

all: lab001 lab002 lab003 lab004 lab005 lab006 lab007 lab008 lab013

%.o: %.c
	echo $(CC) -o $@ $(CFLAGS)
	$(CC) -o $@ $< $(CFLAGS)

index: *.c
	sed -n '/\* lab[0-9]* - /s/...//p' *.c > INDEX

clean:
	rm -f lab??? *.data
