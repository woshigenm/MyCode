assume cs:code

code segment
	;DIV 练习
start:
	;16位除法 商保存在 AX 余数保存在 DX
	;MOV DX, 11H
	;MOV AX, 86A1H
	;MOV BX, 64H
	;DIV BX
	
	;8位除法 商保存在 AL 余数保存在 AH
	;MOV AX, 114H
	;MOV BL, 14H
	;DIV BL
	
	MOV DX, 0020H
	MOV AX, 20H
	MOV BX, 2100H
	DIV BX
	
	MOV AX, 114H
	MOV BL, 14H
	DIV BL
	
	mov ax, 4c00h
	int 21h
	
code ends

end start
