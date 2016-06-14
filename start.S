#include <syscall.h>

.global _start

# Setup the required ABI bits, call main, and then exit syscall.
_start:
	# set rbp to 0 to mark the outermost frame
	xor %rbp, %rbp

	# pop argc from the top of the stack and save it into rdi
	# rdi should contain the first integer argument to the funcion
	pop %rdi
	# copy the stack pointer into rsi
	# rsi should contain the second integer (or pointer) argument
	# now rsi will contain the address of the argv array.
	mov %rsp, %rsi

	# re-align the stack at 16-bytes boundary (because we popped 8 bytes).
	and $0xfffffffffffffff0, %rsp

	call main

	# save the return value from main into rdi
	# rdi is the first argument to syscall
	mov %rax, %rdi
	mov $__NR_exit, %rax
	syscall
