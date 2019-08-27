BITS 64
global brandString
brandString:
	mov r10,rbx
	mov eax, 0x80000000
	cpuid
	cmp eax,0x80000004
	jl .L2
	mov esi,0x80000002
	.L4:
	mov eax,esi
	cpuid	
	mov [rdi],  dword eax
	mov [rdi+4], dword ebx
	mov [rdi+8], dword ecx
	mov [rdi+12], dword edx
	add rdi,0x10
	inc esi
	cmp esi,0x80000004
	jle .L4
	xor rax,rax
	inc rax
	jmp .L3
	.L2:
	mov al,0x0
	.L3:
	mov rbx, r10
	ret
