#include <syscall.h>

/* We could've used the gcc built-in strlen. */
int strlen(char *s) {
	int i = 0;
	for (; *s; i++, s++);
	return i;
}

/* Just a simple wrapper around write syscall. */
int write(char *s, int len) {
	int r;

	__asm__("mov %[syscall_nr], %%rax\n\t"
		"mov %[fd], %%rdi\n\t"
		"syscall"
		: "=a" (r) /* pull result from rax */
		: [syscall_nr] "n" (__NR_write),
		  [fd] "n" (1),
		  "S" (s), /* this goes into rsi */
		  "d" (len) /* this goes into rdx */);

	return r;
}

/*
 * A simple program that outputs all its arguments to stdout,
 * separated by spaces.
 * It returns the error code from write, if write fails.
 */
int main(int argc, char **argv) {
	int i, r = 0;

	for (i = 1; i < argc; i++) {
		if (i > 1) r = write(" ", 1);
		if (r < 0) return -r;

		r = write(argv[i], strlen(argv[i]));
		if (r < 0) return -r;
	}
	if (argc > 1) r = write("\n", 2);
	if (r < 0) return -r;

	return 0;
}
