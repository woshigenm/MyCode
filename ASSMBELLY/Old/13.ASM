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
	mov ds, ax ;a段地址
	
	xor bx, bx ;bx为a段偏移 bx + 16为b段偏移
	
	mov ax, c
	mov es, ax
	
	mov cx, 8
  s:mov al, ds:[bx]; a的值
	add al, ds:[bx + 16]; b的值
	mov es:[bx], al
	inc bx
	loop s
	
	mov ax, 4c00h
	int 21h
	
code ends

end start
