section .data

extern ioperm

section .text

global morse_bip
morse_bip:
	push word 1
	push dword 02h
	push dword 42h
	call ioperm
	add esp,10
	cmp eax,0
	jne deuruim
	mov al, 182 
	out 43h, al 
	mov ax, 4560
	out 42h, al 
	mov al, ah 
	out 42h, al
	in al,61h 
	or al, 00000011b 
	out 61h, al
	mov bx, 25 
	.p1:
		mov cx, 65535 
	.p2:
		dec cx
		jne .p2
		dec bx
		jne .p1
		in al, 61h
		and al, 11111100b 
		out 61h, al
	deuruim: