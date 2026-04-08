assume cs:code

data segment
    db '1. display      '
    db '2. brows        '
    db '3. replace      '
    db '4. modify       '
data ends

stack segment
    db 16 dup (0)
stack ends

;7.9 单词大写
code segment
start:
	mov ax, data
	mov ds, ax
	mov ax, stack
	mov ss, ax
	mov sp, 16
	
	xor bx, bx
	
	mov cx, 4
  s:
	push cx
	
	mov cx, 4
	mov si, 0
	so:
		mov al, ds:[bx + si + 3]
		and al, 11011111B
		mov ds:[bx + si + 3], al
		inc si
	loop so
	
	pop cx
	add bx, 16
	loop s
	
	mov ax, 4c00h
	int 21h
	
code ends

end start
