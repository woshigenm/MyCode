assume cs:code, ds:data

data segment
	dd 100001
	;A1 86 01 00
	dw 100
	;64 00
	dw 0
	;00 00
data ends

code segment
	;DIV 练习
start:
	mov ax, data
	mov ds, ax
	
	MOV DX, DS:[2]
	MOV AX, DS:[0]
	
	DIV WORD PTR DS:[4]
	
	MOV DS:[6], AX
	
	mov ax, 4c00h
	int 21h
	
code ends

end start
