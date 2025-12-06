CC = cc
CFLAGS = -Wall -Wextra -Wfatal-errors -g3 -Werror=vla -Werror=shadow -Wno-unused -Wno-unused-parameter

all: parta partb partc

parta: parta.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/parta parta.c

partb: partb.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/partb partb.c

partc: partc.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/partc partc.c

clean:
	rm -rf build