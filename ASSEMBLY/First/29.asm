assume ds:data, es:table, cs:code, ss:stack

data segment
    db '1975','1976','1977','1978','1979','1980','1981','1982','1983'
    db '1984','1985','1986','1987','1988','1989','1990','1991','1992'
    db '1993','1994','1995'
	
    dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514
    dd 345980,590827,803530,1183000,1843000,2759000,3753000,4649000,5937000
    
    dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793,4037,5635,8226
    dw 11542,14430,15257,17800
data ends

table segment
    db 21 dup ('year summ ne ?? ')
table ends

stack segment
	dw 16 dup(0)
stack ends

;实验8
code segment
start:
	; ds 绑定数据段
	MOV AX, data
	MOV DS, AX
	
	; ss 绑定栈段
	MOV AX, stack
	MOV SS, AX
	MOV SP, 16
	
	; es 绑定数据段
	MOV AX, table
	MOV ES, AX
	
	XOR BP, BP ; BP 为全局变量
	XOR SI, SI
	XOR DI, DI
	
	MOV CX, 21 ; 总共有21行数据, 故 cx = 21
  S:
	PUSH CX ; 保存 cx, 因为 cx 为 loop 的次数, 内有嵌套 
	
	XOR BX, BX ;BX 清零
	MOV CX, 2
	
	PUSH BP
	F:
		MOV AX, DS:[BP]
		MOV ES:[SI + BX], AX
		
		ADD BX, 2
		ADD BP, 2
	LOOP F
	POP BP
	
	MOV BYTE PTR ES:[SI + 04H], ' ' ; 置空格
	
	XOR BX, BX ;BX 清零
	MOV CX, 2
	SO:
		MOV AX, DS:[BP + 84]
		MOV ES:[SI + BX + 05H], AX
		
		ADD BX, 2
		ADD BP, 2
	LOOP SO
	
	MOV BYTE PTR ES:[SI + 09H], ' ' ; 置空格
	
	; 雇员数
	MOV AX, DS:[DI + 84 + 84]
	MOV ES:[SI + 0AH], AX
	
	MOV BYTE PTR ES:[SI + 0CH], ' ' ; 置空格
	
	MOV DX, DS:[BP + 84 - 2]
	MOV AX, DS:[BP + 84 - 4]
	
	DIV WORD PTR DS:[DI + 84 + 84]
	
	MOV ES:[SI + 0DH], AX
	
	POP CX; 回复外侧循环 CX 寄存器
	
	ADD SI, 16
	ADD DI, 2
	LOOP S
	
	MOV AX, 4C00H
	INT 21h
	
code ends

end start
