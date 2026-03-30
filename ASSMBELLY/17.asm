ASSUME CS:CODE,DS:DATA

DATA SEGMENT
    DB 'FUCK YOU FANXIAOCHAO!!!',0
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS,AX
    
    XOR BX,BX
    CALL DISPLAY
    
    CALL CONVERT
    
    CALL DISPLAY
    
    MOV AX, 04C00H
    INT 21H

CONVERT:
    MOV SI,0
    MOV CH, 0
    S:    
        MOV CL, DS:[SI]
        JCXZ OVER
        OR CL,00100000B 
        MOV DS:[SI], CL
        
        INC SI
    JMP SHORT S          
OVER: RET
    
DISPLAY:
    MOV AX, 0B800H
    MOV ES, AX
    
    MOV SI,0
    XOR DI, DI
    MOV CH, 0
    MOV DH, 02H
    S1:
       MOV DL, DS:[SI]
       MOV CL, DL
       JCXZ OVER2     
       MOV ES:[DI + BX],DX
       
       ADD DI,2
       INC SI          
    JMP SHORT S1
OVER2:    
    ADD BX, 160 
    RET 
    
CODE ENDS
END START