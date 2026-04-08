assume cs:code, ss:stack

data segment

    db 'ibm             '
    db 'dec             '
    db 'dos             '
    db 'vax             '
data ends

stack segment
	dw 8 dup(0)
stack ends

code segment
	;7.6 单词大写
start:
	mov ax, data
	mov ds, ax
	mov ss, stack
	mov sp, 16
	
	xor bx, bx
	
	mov cx, 4
	mov si, 0
  s:
	mov bx, 0
	mov ds:[40H], cx
	;push cx
	mov cx, 3
    so:
		mov al, ds:[bx + si]
		and al, 11011111B
		mov ds:[bx + si], al
		inc bx
	loop so
	;pop cx
	mov cx, ds:[40H]
	add	si, 16
	loop s
	
	mov ax, 4c00h
	int 21h
	
code ends

end start