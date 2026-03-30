ASSUME CS:CODES,SS:STACK

STACK SEGMENT
   DW 8 DUP(0) 
STACK ENDS

CODESG SEGMENT
START:    
    MOV AX, 0B800H
    MOV DS, AX
    
    MOV DH, 02H
    MOV AH, 02H
    XOR SI, SI
    
    MOV CX, 25 
S:           
    PUSH CX
    
    MOV DL, 'A'
    MOV AL, 'Z'
    
    XOR BX, BX      
    MOV CX, 26
    SO:
        MOV DS:[BX + SI], DX
        MOV DS:[BX + SI + 52], AX
		
        ADD BX, 2
        INC DL
        DEC AL
    LOOP SO
    
    POP CX
    
    INC DH
    INC AH
    ADD SI, 160
    LOOP S
    
    MOV AX, 4C00H
    INT 21H
    
CODESG ENDS
END START