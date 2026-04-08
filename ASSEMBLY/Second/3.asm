assume code:cs

code segment
    
    MOV AX, 0FFFFH
    MOV DS, AX
    
    MOV AX, 20H
    MOV ES, AX
    
    MOV BX, 0H
    MOV CX, 0CH
S:       
    MOV AL, DS:[BX]
    MOV ES:[BX], AL
    INC BX
    LOOP S
    
    MOV AX, 04C00H
    INT 21
    
code ends        

END