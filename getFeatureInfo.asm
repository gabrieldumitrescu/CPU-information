BITS 64
global getFeatureInfo
getFeatureInfo:
	mov r10,rbx
	mov eax, 0x01
	cpuid
	mov [rdi],   dword ecx
	mov [rdi+4], dword edx
	mov [rdi+8], dword eax
	mov [rdi+12], dword ebx
	mov rbx, r10
	ret
