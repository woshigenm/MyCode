assume cs:code

a segment
	db 1,2,3,4,5,6,7,8
a ends

b segment
	db 1,2,3,4,5,6,7,8
b ends

c segment
	DB 8 DUP(0)
c ends

code segment
	;实验五 (5)
start:
	
	mov ax, a
	mov ds, ax ;ds 为 a 段地址
	
	mov ax, b
	mov es, ax;es 为 b 段地址
	
	xor bx, bx ;bx 置为 0
	
	mov cx, 8
	
	xor ax, ax
  s:mov al, ds:[bx]
	add al, es:[bx]
	
	push ds
	mov dx, c
	mov ds, dx
	mov ds:[bx], al
	pop ds
	
	inc bx
	loop s
	
	mov ax, 4c00h
	int 21h
	
code ends

end start
