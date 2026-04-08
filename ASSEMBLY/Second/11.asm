ASSUME CS:CODE,DS:DATA

DATA SEGMENT
    DB 'BaSiC'
    DB 'iNfOrMaTion'
DATA ENDS

CODE SEGMENT 
START:      
           
    MOV AX, DATA
    MOV DS, AX
    
    MOV CX,5
    MOV BX, 0
    MOV AH, 0
S:     
    MOV AL, DS:[BX] 
    AND AL, 11011111B
    MOV DS:[BX], AL
    INC BX
    LOOP S 

    MOV CX,11
    MOV BX, 5
    MOV AH, 0
SO:     
    MOV AL, DS:[BX]
    OR AL,00100000B
    MOV DS:[BX], AL
    INC BX
    LOOP SO
    
    MOV AX,4C00H
    INT 21H

CODE ENDS
END START