section .text
global beep

beep:
	enter 0, 0
	pusha
	mov eax, 101
	mov ebx, 0x42
	mov ecx, 0x20
	mov edx, 3
	int 0x80

	mov al, 182 
	out 43h, al

	mov eax, [ebp + 8]
	cmp eax, 0
	je .fim
	out 42h, al
	mov al, ah
	out 42h, al

	in al,61h
	or al, 00000011b
	out 61h, al

	mov bx, 500

	.p1:
		mov cx, 65535
	.p2:
		dec cx
		jne .p2
		dec bx
		jne .p1
		in al, 61h;
		and al, 11111100b
		out 61h, al

	.fim:
	popa
	leave
	ret