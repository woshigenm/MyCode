ASSUME CS:CODE

DATA SEGMENT
  db "Beginner's All-purpose Symbolic Instruction Code.", 00
DATA ENDS

CODE SEGMENT
BEGIN:
    ; CALL CLEAR_SCREEN
    
    MOV AX, DATA
    MOV DS, AX
    MOV SI, 0
    CALL LETTERC
    
    MOV DX, 0101H
    MOV CL, 11000010B
    CALL SHOW_STR
    
    MOV AX, 4C00H
    INT 21H

LETTERC:
    PUSH SI
    PUSH CX
CONVERT:   
CONVERT_LOOP:
        MOV CL, DS:[SI] 
        CMP CL, 00      
        JE OVER_CONVERT_LOOP
        
        CMP CL, 'a'
        JB ALPHA
        
        CMP CL, 'z'
        JA ALPHA 
        
        AND CL, 11011111B
        MOV DS:[SI], CL
ALPHA:       
        INC SI
    JMP SHORT CONVERT_LOOP    

OVER_CONVERT_LOOP:
    POP CX    
    POP SI
    RET

; DH 行号 DL 列号 CL 颜色 DS:SI 字符串首地址
SHOW_STR:
    PUSH AX
    PUSH BX
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
ITER_LOOP:
        MOV DL, DS:[SI]
        CMP DL, 0
        JE ITER_LOOP_OVER
        
        MOV ES:[BX], DX
        INC SI
        ADD BX, 2  
    JMP SHORT ITER_LOOP 

ITER_LOOP_OVER:
    POP ES
    POP SI 
    POP DX
    POP BX
    POP AX
    RET

CLEAR_SCREEN:
    PUSH ES      ; 保存关键寄存器
    PUSH AX
    PUSH CX
    PUSH DI
CLEAR:    
    MOV AX, 0B800H
    MOV ES, AX   ; 使用ES访问显存
    
    XOR DI, DI   ; 从显存开头开始
    
    MOV CX, 2000 
    
    MOV AX, 0720H  ; AH=属性, AL=字符
    
    CLD           ; 设置方向向前

    REP STOSW         ; ES:[DI]←AX, DI+2
    
    POP DI
    POP CX
    POP AX
    POP ES        ; 恢复原始ES
    RET
               
CODE ENDS
END BEGIN