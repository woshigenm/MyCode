ASSUME CS:CODE,SS:STACK

STACK SEGMENT
    DW 32 DUP(0)
STACK ENDS

CODE SEGMENT
START:
    MOV AX, STACK
    MOV SS, AX
    MOV SP, 64
    
    MOV AX, CS
    MOV DS, AX
    
    MOV AX, 0
    MOV ES, AX
    
    MOV SI, OFFSET INT7C
    MOV DI, 200H
    
    CLD
    
    MOV CX, OFFSET INT7C_END - OFFSET INT7C
    REP MOVSB  
    
    CLI
    MOV WORD PTR ES:[4 * 7CH + 2], 0
    MOV WORD PTR ES:[4 * 7CH], 200H  
    STI
    
    MOV AH, 0H
    INT 16H
    SUB AL, 30H
    MOV AH, AL
    MOV AL, 00000010B
    INT 7CH 
    
    MOV AX, 4C00H
    INT 21H
         
INT7C:
    JMP SHORT INT7C_S
    TABLE DD CLEAR_SCREEN, SET_FRONT, SET_BACK, SCROLL_LINE
INT7C_S:
    PUSH BX
    
    CMP AH, 3
    JA INT7C_OVER
    
    MOV BL, AH
    MOV BH, 0
    SHL BX, 1
    SHL BX, 1

    CALL DWORD PTR CS:202H[BX]
    
INT7C_OVER:   
    POP BX        
    IRET

INT7C_END:  
    NOP
    
CLEAR_SCREEN:
    PUSH AX
    PUSH CX
    PUSH DI
    PUSH ES
    
    CMP AH, 0H
    JNE CLEAR_SCREEN_OVER
    
    MOV AX, 0B800H
    MOV ES, AX
    
    MOV AX, 0720H 
    
    XOR DI, DI
    
    CLD
    
    MOV CX, 2000
    REP STOSW
CLEAR_SCREEN_OVER:
    POP ES
    POP DI
    POP CX
    POP AX     
    RETF                         
; a b c d e f
SET_FRONT:
    PUSH CX
    PUSH DI
    PUSH AX
    PUSH BX
    
    CMP AH, 1H
    JNE SET_FRONT_OVER
    
    MOV BX, 0B800H
    MOV ES, BX
    
    MOV DI, 1H
    
    MOV CX, 2000
SET_FRONT_LOOP:
    MOV ES:[DI], AL
    ADD DI, 2H
    LOOP SET_FRONT_LOOP   

SET_FRONT_OVER:
    POP BX
    POP AX    
    POP DI
    POP CX
    RETF
    
SET_BACK:
    PUSH DI
    PUSH CX
    PUSH ES
    PUSH AX
    PUSH BX
    
    CMP AH, 2H
    JNE SET_BACK_OVER
    
    MOV BX, 0B800H
    MOV ES, BX
    
    MOV DI, 1H
    
    MOV CL, 4
    SHL AL, CL
    MOV BL, AL
    
    MOV CX, 2000
SET_BACK_LOOP:
    MOV AL, ES:[DI]
    AND AL, 10001111B
    OR AL, BL 
    MOV ES:[DI], AL
    ADD DI, 2H
    LOOP SET_BACK_LOOP 

SET_BACK_OVER:
    POP BX
    POP AX
    POP ES
    POP CX
    POP DI
    RETF

SCROLL_LINE:
    PUSH AX
    PUSH DS
    PUSH SI
    PUSH DI
    PUSH CX
    PUSH ES
    
    CMP AH, 3H
    JNE SCROLL_LINE_OVER
    
    MOV AX, 0B800H 
    MOV DS, AX
    
    MOV ES, AX
    
    MOV SI, 160
    
    MOV DI, 0
    
    CLD
    
    MOV CX, 1920 
    REP MOVSW
    
    MOV DI, 160 * 24  ; 最后一行起始偏移（第24行）
    MOV AX, 0720H     ; 空格字符(20h) + 属性07h（灰底黑字）
    MOV CX, 80        ; 80字符
    REP STOSW         ; 填充整行

SCROLL_LINE_OVER:    
    POP ES
    POP CX
    POP DI
    POP SI
    POP DS
    POP AX
    RETF
                
CODE ENDS
END START