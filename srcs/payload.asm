[BITS 64]

global		inject_func:function
global		inject_size:data
global		code_size:data

inject_size	dq	end - inject_func
code_size	dq	variables - inject_func

inject_func:
	push rax 
	push rbx 
	push rcx 
	push rdx 
	push rsi 
	push rdi 
	push rsp 
	push rbp
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15

	mov		rax, [rel addr]
	mov		rcx, [rel size]
	mov		rdx, [rel key]
	add		rcx, rax
	.loop	xor		byte[rax], dl
		ror		rdx, 8
		inc		rax
		cmp		rax, rcx
		jnz		.loop

	mov rax, 0x1
	mov rdi, 0x1
	push 0x444f4f57
	push 0x2e2e2e2e
	mov rsi, rsp
	mov rdx, 0xe
	syscall
	pop r15
	pop r15

	mov rax, 0x1
	mov rdi, 0x1
	push 0x00000a2e
	push 0x2e2e2e59
	mov rsi, rsp
	mov rdx, 0xe
	syscall
	pop rax
	pop rax

	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rbp
	pop rsp 
	pop rdi 
	pop rsi 
	pop rdx 
	pop rcx 
	pop rbx 
	pop rax 

;	mov		rax, [rel addr]
;	jmp		rax
	jmp	0x11111111

variables:
key:		dq	0x4444444444444444
addr:		dq	0x2222222222222222
size:		dq	0x3333333333333333

end:
