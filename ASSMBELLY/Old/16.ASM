assume cs:code, ds:data

data segment
	db 'BaSic'
	db 'iNfOrMaTiOn'
data ends

code segment
	;7.4 大小写转化
start:
	
	mov ax, data
	mov ds, ax
	
	xor bx, bx
	
	mov cx, 5
  s:mov al, ds:[bx]
	and al, 11011111B
	mov ds:[bx], al
	inc bx
	loop s
	
	mov bx, 5
	mov cx, 11
  so:mov al, ds:[bx]
	or al, 00100000B
	mov ds:[bx], al
	inc bx
	loop so
	
	mov ax, 4c00h
	int 21h
	
code ends

end start
