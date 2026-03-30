assume cs:code, ds:data

data segment
	db 'iNfOrMaTiOn'
	db 'FANXIAOCHAO'
data ends

code segment
	;7.4 大小写转化
start:
	
	mov ax, data
	mov ds, ax
	
	xor bx, bx
	
	mov cx, 11
  
  s:mov al, ds:[bx]
	and al, 11011111B
	mov ds:[bx], al
	
	mov ah, ds:[bx + 11]
	or ah, 00100000B
	mov ds:[bx + 11], ah
	
	inc bx
	loop s
	
	mov ax, 4c00h
	int 21h
	
code ends

end start
