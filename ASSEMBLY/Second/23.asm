ASSUME CS:CODE

STACK SEGMENT
    DW 16 DUP(0)
STACK ENDS

DATA SEGMENT
  db '1975',0, '1976',0, '1977',0, '1978',0, '1979',0, '1980',0, '1981',0, '1982',0, '1983',0
  db '1984',0, '1985',0, '1986',0, '1987',0, '1988',0, '1989',0, '1990',0, '1991',0, '1992',0
  db '1993',0, '1994',0, '1995',0

  dd 16, 22, 382, 1356, 2390, 8000, 16000, 24486, 50065, 97479, 140417, 197514
  dd 345980, 590827, 803530, 1183000, 1843000, 2759000, 3753000, 4649000, 5937000

  dw 3, 7, 9, 13, 28, 38, 130, 220, 476, 778, 1001, 1442, 2258, 2793, 4037, 5635, 8226
  dw 11542, 14430, 15257, 17800
DATA ENDS

TMP SEGMENT
    DB 16 DUP(0)
TMP ENDS

CODE SEGMENT
START:
    MOV AX, STACK
    MOV SS, AX
    MOV SP, 32
    
    MOV AX, DATA
    MOV DS, AX
    MOV SI, 0
    MOV DH, 1
    
    MOV BX, 069H 
    MOV DI, 0BDH
    MOV CX, 21
INNER_LOOP:  
        PUSH DS
        PUSH CX
        PUSH SI
        
        MOV DL, 1H
        MOV CL, 7H
        
        CALL SHOW_STR
        
        PUSH DS ; DS = DATA
        PUSH DX
        
        MOV DX, DS:[BX + 2]
        MOV AX, DS:[BX] 
        PUSH AX
        
        MOV AX, TMP
        MOV DS, AX
        
        POP AX
        CALL DWDTOC
        POP DX
        
        ADD DL, 20
        XOR SI, SI
        CALL SHOW_STR ; DS = TMP
        POP DS ; DS = DATA
        
        PUSH DS
        
        MOV AX, DS:[DI]
        PUSH AX
        MOV AX, TMP
        MOV DS, AX
        POP AX 
        
        CALL WDTOC
        
        ADD DL, 20
        XOR SI, SI
        CALL SHOW_STR ; DS = TMP
        
        POP DS ; DATA
        
        PUSH DX
        MOV DX, DS:[BX + 2]
        MOV AX, DS:[BX]
        MOV CX, DS:[DI]
        
        CALL DIVDW
        
        PUSH AX
        MOV AX, TMP
        MOV DS, AX
        POP AX
        CALL DWDTOC
        
        POP DX
        
        MOV CL, 7H
        ADD DL, 20
        XOR SI, SI
        CALL SHOW_STR
         
        POP SI
        
        ADD DI, 2
        ADD SI, 5
        ADD BX, 4
        INC DH
        POP CX
        POP DS
    LOOP INNER_LOOP
        
    MOV AX, 04C00H
    INT 21H

; DH 行号 DL 列号 CL 颜色 DS:SI 字符串首地址
SHOW_STR:
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    PUSH SI
    PUSH ES
PRINT:
    MOV AX, 0B800H
    MOV ES, AX    
    
    DEC DL
    ADD DL, DL ; 2*(N-1)
    DEC DH
    MOV AL, 0A0H
    MUL DH     ; A0*(N-1)
    
    MOV DH, 0
    ADD AX, DX
    
    MOV BX, AX
    
    MOV DH, CL
    XOR CX, CX
ITER_LOOP:
        MOV DL, DS:[SI]
        MOV CL, DL
        JCXZ ITER_LOOP_OVER
        
        MOV ES:[BX], DX
        INC SI
        ADD BX, 2  
    JMP SHORT ITER_LOOP 

ITER_LOOP_OVER:
    POP ES
    POP SI 
    POP DX
    POP CX
    POP BX
    POP AX
    RET

; DX 数据高 16 位, AX 数据低 16 位, CX 除数
; DX 结果数据高 16 位, AX 结果数据低 16 位, CX 余数
DIVDW:
    PUSH BX
DIV_S:
    PUSH AX ; AX = L
    
    MOV AX, DX
    MOV DX, 0H
    DIV CX
    ; AX = INT(H/N) DX = REM(H/N)
    
    MOV BX, AX
    
    POP AX ; AX = L
    DIV CX
    ; AX = INT(REM + L) DX = REM(REM + L)
   
    MOV CX, DX
    MOV DX, BX
    
    POP BX
    RET

; AX = WORD  DS:SI 字符串存储地址   
WDTOC:
    PUSH SI
    PUSH BX
    PUSH DX
    PUSH CX
    PUSH DI
    PUSH AX    
CONVERT:
    MOV BX, 10
    XOR SI, SI
CONVERT_LOOP:
        MOV DX, 0
        
        DIV BX
        
        ADD DL, 30H
        MOV DS:[SI], DL
        INC SI
        
        MOV CX, AX
        JCXZ CONVERT_LOOP_OVER
    JMP SHORT CONVERT_LOOP     
CONVERT_LOOP_OVER:
    MOV BYTE PTR DS:[SI], 0
    
    MOV AX, SI
    
    DEC SI
    MOV DI, SI
    
    MOV DX, 0
    MOV BX, 2
    DIV BX
    
    MOV CX, AX
    
    MOV SI, 0
REVERSE_lOOP:
    JCXZ REVERSE_lOOP_OVER 
    MOV AL, DS:[SI]
    MOV AH, DS:[DI]
    
    MOV DS:[DI], AL
    MOV DS:[SI], AH
    
    INC SI
    DEC DI
    LOOP REVERSE_lOOP
REVERSE_lOOP_OVER:    
    POP AX
    POP DI
    POP CX
    POP DX
    POP BX 
    POP SI
    RET
    
; DX = 高十六位 AX = 低十六位  DS:SI 字符串存储地址   
DWDTOC:
    PUSH SI
    PUSH BX
    PUSH DX
    PUSH CX
    PUSH DI
    PUSH AX    
DCONVERT:
        XOR SI, SI
DCONVERT_LOOP:
        MOV CX, 10
        
        CALL DIVDW
        
        ADD CL, 30H
        MOV DS:[SI], CL
        INC SI
        
        MOV CX, AX
        JCXZ DCONVERT_LOOP_OVER
    JMP SHORT DCONVERT_LOOP     
DCONVERT_LOOP_OVER:
    MOV BYTE PTR DS:[SI], 0
    
    MOV AX, SI
    
    DEC SI
    MOV DI, SI
    
    MOV DX, 0
    MOV BX, 2
    DIV BX
    
    MOV CX, AX
    
    MOV SI, 0
DREVERSE_lOOP:
    JCXZ DREVERSE_lOOP_OVER 
    MOV AL, DS:[SI]
    MOV AH, DS:[DI]
    
    MOV DS:[DI], AL
    MOV DS:[SI], AH
    
    INC SI
    DEC DI
    LOOP DREVERSE_lOOP
DREVERSE_lOOP_OVER:    
    POP AX
    POP DI
    POP CX
    POP DX
    POP BX 
    POP SI
    RET    

CODE ENDS
END START