ASSUME CS:CODE,DS:DATA,ES:TABLE

data segment
  db '1975', '1976', '1977', '1978', '1979', '1980', '1981', '1982', '1983'
  db '1984', '1985', '1986', '1987', '1988', '1989', '1990', '1991', '1992'
  db '1993', '1994', '1995'

  dd 16, 22, 382, 1356, 2390, 8000, 16000, 24486, 50065, 97479, 140417, 197514
  dd 345980, 590827, 803530, 1183000, 1843000, 2759000, 3753000, 4649000, 5937000

  dw 3, 7, 9, 13, 28, 38, 130, 220, 476, 778, 1001, 1442, 2258, 2793, 4037, 5635, 8226
  dw 11542, 14430, 15257, 17800
data ends

table segment
  db 21 dup ('year summ ne ?? ')
table ends

CODE SEGMENT
START:
    MOV AX,DATA
    MOV DS, AX
    
    MOV AX, TABLE
    MOV ES, AX
              
    MOV CX, 21   
S2:        
    MOV AX, DS:[BX]
    MOV ES:[SI], AX
    
    MOV AX, DS:[BX + 2]
    MOV ES:[SI + 2], AX
    
    MOV AX, DS:[BX + 84]
    MOV ES:[SI + 5], AX
    
    MOV AX, DS:[BX + 86]
    MOV ES:[SI + 7], AX
    
    MOV AX, DS:[DI + 168]
    MOV ES:[SI + 0AH], AX 
                     
    MOV AX, DS:[BX + 84]
    MOV DX, DS:[BX + 86]
    DIV WORD PTR DS:[DI + 168]
    
    MOV ES:[SI + 0DH], AX
    
    ADD BX, 4 
    ADD DI, 2
    ADD SI, 16
    LOOP S2
    
    MOV DH, 1 ; DH 行号 
    MOV DL, 1 ; DL 列号
    MOV CL, 2H ; 颜色
    MOV AX, DATA
    MOV DS, AX
    MOV SI, 0H ; DS:SI 为字符串首地址
    MOV CX, 21
S3: 
    
    CALL SHOW_STR 
    LOOP S3
    
    MOV AX, 04C00H
    INT 21H
    
DTOC:
    PUSH SI
CONVERT:
        MOV CX, 10
        CALL DIVDW 
        
        INC SI
        JCXZ RUN
        
        ADD CX, 30H
        MOV DS:[SI], CL
        
    JMP SHORT CONVERT
RUN:
    MOV BYTE PTR DS:[SI], 0 
    
    MOV DI, SI
    
    MOV AX, DI
    MOV BL, 2
    DIV BL
    
    DEC DI 
    MOV SI, 0
    
    XOR CX, CX
    MOV CL, AL
    REVERSE_LOOP: 
        MOV AL, DS:[DI]
        MOV BL, DS:[SI]
        MOV DS:[DI], BL
        MOV DS:[SI], AL 
        
        INC SI
        DEC DI    
    LOOP REVERSE_LOOP
     
    POP SI
        
    RET
     
DIVDW:
    PUSH SI
OVERFLOW:       
    MOV BX, AX
    
    MOV AX, DX
    MOV DX, 0
    DIV CX
    
    MOV SI, AX
    MOV AX, BX
    DIV CX
    
    MOV CX, DX
    MOV DX, SI 
    
    POP SI
    RET
    
SHOW_STR:
    PUSH SI
FANXIAOCHAO:  
    MOV AX, 0B800H
    MOV ES, AX 
    
    MOV AL, 0A0H  
    MUL DH 
    
    MOV BX, AX
    
    ADD DL, DL
    
    MOV DI, AX
    MOV DH, CL
    
    XOR CX,CX
S:             
    MOV CL, DS:[SI]
    JCXZ OVER
    MOV DL, CL
    
    MOV ES:[BX + DI - 162], DX
    ADD DI, 2
    INC SI 
    JMP SHORT S
    
OVER:
    POP SI     
    RET
        
CODE ENDS
END START