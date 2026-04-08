assume cs:code

data segment

    db '1. file         '
    db '2. edit         '
    db '3. search       '
    db '4. view         '
    db '5. options      '
    db '6. help         '
	
data ends

code segment
	;7.6 首单词大写
start:
	mov ax, data
	mov ds, ax
	
	xor bx, bx
	mov si, 3
	
	mov cx, 6
  s:mov al, ds:[bx + si]
	and al, 11011111B
	mov ds:[bx + si], al
	add bx, 16
	loop s
	
	mov ax, 4c00h
	int 21h
	
code ends

end start