all: hello echo

.PHONY: all clean

hello: hello.c start.S
	gcc -Wall -nostdlib -o $@ $^

echo: echo.c start.S
	gcc -Wall -nostdlib -fno-builtin -o $@ $^

clean:
	rm -f hello echo
