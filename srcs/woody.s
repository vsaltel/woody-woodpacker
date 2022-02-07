section .text
	global _start 

_start:
	push rax 
	push rbx 
	push rcx 
	push rdx 
	push rsi 
	push rdi 
	push rsp 
	push rbp

	mov rax, 0x1
	mov rdi, 0x1
	push 0x444f4f57
	push 0x2e2e2e2e
	mov rsi, rsp
	mov rdx, 0xe
	syscall

	mov rax, 0x1
	mov rdi, 0x1
	push 0x00000a2e
	push 0x2e2e2e59
	mov rsi, rsp
	mov rdx, 0xe
	syscall

	jmp 0x11111111

	pop rax 
	pop rbx 
	pop rcx 
	pop rdx 
	pop rsi 
	pop rdi 
	pop rsp 
	pop rbp
