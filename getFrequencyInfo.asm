BITS 64
global getFrequencyInfo
getFrequencyInfo:
	mov r10,rbx
	mov eax, 0x16
	cpuid
	mov [rdi],   ax
	mov [rdi+2], bx
	mov [rdi+4], cx
	mov rbx, r10
	ret
