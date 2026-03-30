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

TMP segment
  db 10 dup (0)
TMP ends

CODE SEGMENT
START:
    CALL CLEAR_SCREEN
    
    MOV AX,DATA
    MOV DS, AX
    
    MOV AX, TABLE
    MOV ES, AX
              
    MOV CX, 21   
S:        
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
    LOOP S
    
    MOV AX, table
    MOV DS, AX   
    MOV SI, 0
    MOV DH, 1
    
    MOV BX, 0
    MOV CX, 21    
INNER_LOOP:
        PUSH DS
        PUSH CX
        PUSH SI
        ; DS = TABLE
        
        MOV DL, 1
        MOV CL, 7
        CALL SHOW_STR
        
        PUSH DS ; DS = TABLE
        PUSH DX 
        MOV DX, DS:[BX + 7] ;'year summ ne ?? '
        MOV AX, DS:[BX + 5]
        
        PUSH AX
        MOV AX, TMP
        MOV DS, AX ; DS = TMP
        POP AX
        CALL DWDTOC
        
        POP DX

        ADD DL, 20 
        XOR SI, SI
        CALL SHOW_STR
        POP DS ; DS = TABLE 
        
        MOV AX, DS:[BX + 10]
        PUSH DS
        PUSH AX
        MOV AX, TMP
        MOV DS, AX ; DS = TMP
        POP AX
        CALL WDTOC
        
        ADD DL, 20 
        XOR SI, SI
        CALL SHOW_STR
        
        POP DS ; DS = TABLE 
        
        PUSH DS ; DS = TABLE
        PUSH DX
        MOV DX, DS:[BX + 7] 
        MOV AX, DS:[BX + 5]
        PUSH CX
        MOV CX, DS:[BX + 10]
        
        CALL DIVDW
        
        PUSH AX
        MOV AX, TMP
        MOV DS, AX  ; DS = TMP
        POP AX
        CALL DWDTOC
        
        POP CX
        POP DX
        ADD DL, 20 
        XOR SI, SI
        CALL SHOW_STR
        
        POP DS ; DS = TABLE       
        
        POP SI
        ADD SI, 16
        ADD BX, 16
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
        SUB CL, 20H
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
    MOV BYTE PTR DS:[SI], 20H
    
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
    MOV BYTE PTR DS:[SI], 20H
    
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

CLEAR_SCREEN:
    PUSH ES      ; 保存关键寄存器
    PUSH AX
    PUSH CX
    PUSH DI
    
    MOV AX, 0B800H
    MOV ES, AX   ; 使用ES访问显存
    
    XOR DI, DI   ; 从显存开头开始
    
    ; 正确循环次数：80列×25行=2000字符，每字符2字节
    MOV CX, 2000 ; 4000字节/2 = 2000次写入
    
    ; 空格字符(20H) + 黑底白字属性(07H)
    MOV AX, 0720H  ; AH=属性, AL=字符
    
    CLD           ; 设置方向向前
    
    REP STOSW         ; ES:[DI]←AX, DI+2
    
    POP DI
    POP CX
    POP AX
    POP ES        ; 恢复原始ES
    RET
        
CODE ENDS
END START
