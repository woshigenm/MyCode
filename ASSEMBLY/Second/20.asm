ASSUME SS:STACK,CS:CODE

CODE SEGMENT
START:
    MOV AX, 0CA00H; L
    MOV DX, 3B9AH; H
    MOV CX, 0AH  ; N
    
    CALL DIVDW
   
    MOV AX, 4C00H
    INT 21H    
        
DIVDW:
     PUSH SI
FUCK:       
    MOV BX, AX
    
    MOV AX, DX
    MOV DX, 0
    DIV CX
    ; AX=INT(H/N)   DX=REM(H/N)
    MOV SI, AX
    MOV AX, BX
    DIV CX
    ; AX=INT(REM(H/N)*1000H+L)   DX=REM(REM(H/N)*1000H+L)
    MOV CX, DX
    MOV DX, SI
    
    POP SI
    RET
    
CODE ENDS
END START