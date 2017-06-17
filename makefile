#!/usr/bin/env make -f

CC      = clang
CFLAGS  = -g
LDFLAGS = -lc -lm
OBJ     = main.o byte.o sha1.o md5.o hmac.o
OUT     = a.out

all: test

test: $(OUT)
	./$(OUT)

debug: $(OUT)
	lldb $(OUT)

clean:
	rm -rf $(OBJ) $(OUT)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $?

