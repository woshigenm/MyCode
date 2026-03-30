assume cs:code

data segment

    db 'ibm             '
    db 'dec             '
    db 'dos             '
    db 'vax             '

data ends

code segment
	;7.6 单词大写
start:
	mov ax, data
	mov ds, ax
	
	xor bx, bx
	
	mov cx, 4
	mov si, 0
  s:
	mov bx, 0
	push cx
	mov cx, 3
    so:
		mov al, ds:[bx + si]
		and al, 11011111B
		mov ds:[bx + si], al
		inc bx
	loop so
	pop cx
	add	si, 16
	loop s
	
	mov ax, 4c00h
	int 21h
	
code ends

end start