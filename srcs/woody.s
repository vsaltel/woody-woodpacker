section .text
	global _start 

_start:
	mov rax, 0x1
	mov rdi, 0x1
	push 0x444f4f57
	push 0x2e2e2e2e
	mov rsi, rsp
	mov rdx, 0xe
	syscall

	mov rax, 0x1
	mov rdi, 0x1
	push 0x0000002e
	push 0x2e2e2e59
	mov rsi, rsp
	mov rdx, 0xe
	syscall

	mov rax, 0x3c
	mov rdi, 0x0
	syscall
