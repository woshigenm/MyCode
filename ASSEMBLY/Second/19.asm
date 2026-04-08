ASSUME DS:DATA,CS:CODE

DATA SEGMENT
  DB 'WELCOME TO MASM!!!', 0
DATA ENDS

CODE SEGMENT
START:
    MOV DH, 3 ; DH 行号 
    MOV DL, 3 ; DL 列号
    MOV CL, 2H ; 颜色
    MOV AX, DATA
    MOV DS, AX
    MOV SI, 0H ; DS:SI 为字符串首地址
    
    MOV AX, 0B800H
    MOV ES, AX
    
    CALL SHOW_STR
    
    MOV AX, 4C00H
    INT 21H

SHOW_STR:  
    MOV AX, 0B800H
    MOV ES, AX 
    
    ; 计算行偏移值
    MOV AL, 0A0H  
    MUL DH 
    
    MOV BX, AX
    
    MOV AL, 2
    MUL DL
    
    MOV DI, AX
    MOV DH, CL
    
    XOR CX,CX
S:             
    MOV CL, DS:[SI]
    JCXZ OVER
    MOV DL, CL
    
    MOV ES:[BX + DI - 162], DX
    ADD DI, 2
    INC SI 
    JMP SHORT S
    
OVER:     
    RET
    
CODE ENDS
END START
