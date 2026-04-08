ASSUME CS:CODE,DS:DATA

DATA SEGMENT
    DW 1,2,3,4,5,6,7,8
    DD 0,0,0,0,0,0,0,0
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX
    
    XOR SI, SI
    MOV DI, 16
    MOV CX, 8
S:  
    MOV BX, DS:[SI]
    CALL CUBE
    MOV DS:[DI], AX
    MOV DS:[DI + 2], DX
    ADD SI, 02H
    ADD DI, 04H
    LOOP S  
    
    MOV AX, 04C00H
    INT 21H
    
    ;参数: (BX)=N
    ;结果: (DX:AX)=N^3 
CUBE:
    MOV AX, BX
    MUL BX
    MUL BX
    RET
    
CODE ENDS
END START