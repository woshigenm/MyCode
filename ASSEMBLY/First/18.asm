assume cs:code, ds:data

data segment
	db 'welcome to masm!'
	db '................'
data ends

code segment
	;7.2 字符串复制
start:
	
	mov ax, data
	mov ds, ax
	
	xor si, si
	xor di, di
	
	mov cx, 8
  
  s:mov ax, ds:[si]
	mov ds:[si + 16], ax
	add si, 2
	loop s
	
	mov ax, 4c00h
	int 21h
	
code ends

end start
