assume code:cs

code segment  
    
    MOV AX,0FFFFH
    MOV DS, AX
    
    MOV BX, 0H
    MOV DX, 0    
    MOV AH, 0  
    
    MOV CX, 0CH
S:
    MOV AL, DS:[BX]
    
    ADD DX, AX      
    INC BX
    LOOP S 
    
    MOV AX, 04C00H
    INT 21
    
code ends

end