ASSUME CS:CODE,DS:DATA

DATA SEGMENT
    DB 'FUCK YOU FANXIAOCHAO!!!'
    DB 23 ; STRING LENGTH
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS,AX
    
    MOV CX,DS:[23]
    CALL CONVERT
    
    MOV CX,DS:[23]
    CALL DISPLAY
    
    MOV AX, 04C00H
    INT 21H

CONVERT:
    MOV SI,0
    S:    
        OR BYTE PTR [SI], 00100000B 
        INC SI
    LOOP S      
    RET
    
DISPLAY:
    MOV AX, 0B800H
    MOV ES, AX
    
    MOV SI,0
    XOR DI, DI
    MOV DH, 02H
    S1:
       MOV DL, DS:[SI]     
       MOV ES:[DI],DX
       
       ADD DI,2
       INC SI          
    LOOP S1
    RET
    
CODE ENDS
END START