BITS 64
global vendorID
vendorID:
	mov r10, rbx
	xor rax,rax
	cpuid
	mov [rdi], ebx
	mov [rdi+4], edx
	mov [rdi+8], ecx
	mov [rdi+12],dword 0
	mov rbx, r10
	ret

