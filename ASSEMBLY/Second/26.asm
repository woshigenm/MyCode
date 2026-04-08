ASSUME CS:CODE

STACK SEGMENT
    DW 128 DUP(0)
STACK ENDS

CODE SEGMENT      
START:
    MOV AX, STACK
    MOV SS, AX    
    MOV SP, 256
    
    MOV AX, 0H
    MOV ES, AX
    
    MOV AX, CS
    MOV DS, AX
    
    MOV DI, 200H
    MOV SI, OFFSET DO0_CODE
    MOV CX, OFFSET DO0_CODE_END - OFFSET DO0_CODE 
    
    CLD
    
    REP MOVSB   
    
    CLI
    MOV WORD PTR ES:[2], 0H
    MOV WORD PTR ES:[0], 200H
    STI
    
    ; CALL CLEAR_SCREEN
    MOV BX, RUN   
    PUSH BX
    ;INT 0
    MOV AX, 1000H
    MOV BL, 1
    DIV BL
     
run:MOV AX, 04C00H
    INT 21H

DO0_CODE:
    JMP SHORT DO0_START

MY_MSG:
    DB 'YOU  DESTROY YOUR DOS!!!',0  

DO0_START:    
    MOV AX, CS
    MOV DS, AX
    
    MOV AX, 0B800H
    MOV ES, AX  
    MOV SI, 200H
    ADD SI, OFFSET MY_MSG - OFFSET DO0_CODE  
    MOV DI, 10*160+36
    MOV CH, 2
PRINT:  
        MOV CL, DS:[SI]
        CMP CL, 0
        JE OVER_PRINT
        MOV ES:[DI], CX
        ADD DI, 2
        INC SI
    JMP SHORT PRINT
    
OVER_PRINT:
    MOV BP, SP
    MOV BX, [BP+6]
    MOV [BP], BX
    IRET
        
DO0_CODE_END:
    NOP

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
END START
