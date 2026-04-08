ASSUME CS:CODE, SS:STACK

STACK SEGMENT
    DW 64 DUP(0)
STACK ENDS

DATA SEGMENT
    EXIT_FLAG DB 0
DATA ENDS 

CODE SEGMENT
START:
    MOV AX, STACK
    MOV SS, AX
    MOV SP, 128
    
    CALL INSTALL_INT9 
    
    MOV AX, 0
    MOV ES, AX ; 0:200 IP 0:202 CS
    
    MOV AX, 20H
    MOV DS, AX
    
    PUSH ES:[4 * 9] ; IP
    POP DS:[0]
    PUSH ES:[4 * 9 + 2] ; CS
    POP DS:[2]
    
    CLI
    MOV WORD PTR ES:[4 * 9], 204H 
    MOV WORD PTR ES:[4 * 9 + 2], 0 
    STI
    
    CALL DELAY
    
    MOV AX, 0
    MOV ES, AX
    
    CLI
    PUSH DS:[0]
    POP ES:[4 * 9]
    PUSH DS:[2]
    POP ES:[4 * 9 + 2]   
    STI
        
    MOV AX, 4C00H
    INT 21H

INSTALL_INT9:
    PUSH AX
    PUSH ES
    PUSH DS
    PUSH DI
    PUSH SI
    PUSH CX
    
    MOV AX, 0
    MOV ES, AX ; 0:200 IP 0:202 CS
    
    MOV AX, CS
    MOV DS, AX
    
    MOV SI, OFFSET INT9
    MOV DI, 204H
    
    CLD
    
    MOV CX, OFFSET INT9_END - OFFSET INT9 
    REP MOVSB 
    
INSTALL_INT9_OVER:
    POP CX
    POP SI
    POP DI
    POP DS
    POP ES
    POP AX
    RET

INT9:
    PUSH AX
    PUSH BX
    PUSH ES
    PUSH DS
    PUSH CX
    
    PUSHF
    MOV AX, 20H
    MOV DS, AX
    CALL DWORD PTR DS:[0]
    
    MOV BX, 0B800H
    MOV ES, BX
    
    IN AL, 60H
    CMP AL, 1EH
    JNE INT9_OVER    
    
    MOV AX, DATA
    MOV DS, AX 
A_LOOP:
    IN AL, 60H
    CMP AL, 9EH
    MOV DS:[EXIT_FLAG], 0 
    JE A_LOOP_OP 
    JMP SHORT A_LOOP    
    
A_LOOP_OP:
    
    MOV DS:[EXIT_FLAG], 1
    
    MOV AL, 'A'
    MOV AH, 02H
    
    CLD
    
    MOV BX, 0B800H
    MOV ES, BX
    MOV DI, 0
    
    MOV CX, 2000
    REP STOSW
                
INT9_OVER:
    POP CX
    POP DS
    POP ES
    POP BX
    POP AX
    IRET    
INT9_END:
    NOP
    
DELAY:
   PUSH DX
   PUSH AX
   PUSH DS
   
   MOV AX, DATA
   MOV DS, AX
    
   MOV DX, 0FFFFH
   MOV AX, 0FFFFH
DELAY_LOOP:
    CMP BYTE PTR DS:[EXIT_FLAG], 1
    JE DELAY_OVER
    SUB AX, 1
    SBB DX, 0
    CMP DX, 0
    JNE DELAY_LOOP
    CMP AX, 0    
    JNE DELAY_LOOP

DELAY_OVER:
   POP DS   
   POP AX
   POP DX
   RET 
           
CODE ENDS
END START