assume cs:code

a segment
	dw 1,2,3,4,5,6,7,8,9,0AH,0BH,0CH,0DH,0EH,0FH,0FFH
a ends

b segment
	dw 0,0,0,0,0,0,0,0
b ends

code segment
	;实验五 (6)
start:

	mov ax, a
	mov ds, ax
	mov ax, b
	mov ss, ax
	mov sp, 16
	
	xor bx, bx
	
	mov cx, 8
  s:push ds:[bx]
	add bx, 2
	loop s
	
	mov ax, 4c00h
	int 21h
	
code ends

end start
