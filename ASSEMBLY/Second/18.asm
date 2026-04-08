ASSUME CS:CODE,DS:DATA
; BP BX SI DI
DATA SEGMENT
    DB 'FUCK', 0
    DB 'YOU ', 0
    DB 'FAN ', 0
    DB 'XIAO', 0
    DB 'CHAO', 0    
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX
    
    XOR BP, BP
    MOV CX, 5
FUCK:
    PUSH CX
    MOV SI, BP
    
    CALL CONVERT
    
    MOV SI, BP
    CALL DISPLAY
    
    ADD BP, 5
    
    POP CX
LOOP FUCK

    MOV AX, 04C00H
    INT 21H
    
CONVERT: 
    MOV CH, 0
    S:    
        MOV CL, DS:[SI]
        JCXZ OVER
        OR CL,00100000B 
        MOV DS:[SI], CL
        
        INC SI
    JMP SHORT S          
OVER:
    RET
    
DISPLAY:
    MOV AX, 0B800H
    MOV ES, AX
    
    MOV CH, 0
    MOV DH, 02H
    
    XOR DI, DI
    S1:
       MOV DL, DS:[SI]
       MOV CL, DL
       JCXZ OVER2
          
       MOV ES:[DI + BX],DX
       
       INC SI
       ADD DI, 2          
    JMP SHORT S1
OVER2:    
    ADD BX, 160 
    RET 
    
CODE ENDS
END START