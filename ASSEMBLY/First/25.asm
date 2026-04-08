assume ds:data, es:table, cs:code

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

;实验8 改版
code segment
start:
	; ds 绑定数据段
	MOV AX, data
	MOV DS, AX
	
	; es 绑定数据段
	MOV AX, table
	MOV ES, AX
	
	MOV CX, 21 ; 总共有21行数据, 故 cx = 21
FIRST:

	MOV AX, DS:[BX]
	MOV ES:[SI], AX
	
	MOV AX, DS:[BX + 02H]
	MOV ES:[SI + 02H], AX
	
	MOV AX, DS:[BX + 054H]
	MOV ES:[SI + 05H], AX
	
	MOV AX, DS:[BX + 056H]
	MOV ES:[SI + 07H], AX
	
	; 雇员数
	MOV AX, DS:[DI + 0A8H]
	MOV ES:[SI + 0AH], AX
	
	; 计算人均收入
	MOV AX, DS:[BX + 054H]
	MOV DX, DS:[BX + 056H]
	
	DIV WORD PTR DS:[DI + 0A8H]
	
	MOV ES:[SI + 0DH], AX
	
	ADD SI, 010H
	ADD DI, 02H
	ADD BX, 04H
	
	LOOP FIRST
	
	MOV AX, 4C00H
	INT 21h
	
code ends

end start
