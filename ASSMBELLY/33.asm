ASSUME CS:CODE

CODE SEGMENT
    TABLES DB '0123456789ABCDEF'
START:
    MOV AL, 0FAH
    ; CALL SHOWBYTE  
    
    MOV CL, 4
    SHL AX, CL
    SHR AL, CL
    
    MOV BX, 0B800H
    MOV ES, BX

    MOV BH, 0
    MOV BL, AH                  
    MOV AH, CS:TABLES[BX]
    MOV ES:[160*12+2*40], AH

    MOV BH, 0
    MOV BL, AL                       
    MOV AL, CS:TABLES[BX]
    MOV ES:[160*12+2*40 + 2], AL   

    MOV AX, 4C00H
    INT 21H 

; AL 为要显示的数据 AL 高四位和低四位分别打印
SHOWBYTE:   
        JMP SHORT SHOW
        TABLE DB '0123456789ABCDEF'    
SHOW:
    PUSH AX
    PUSH BX
    PUSH CX
    
    MOV BX, CS
    MOV DS, BX
    
    MOV BX, 0B800H
    MOV ES, BX
    
    MOV CL, 4
    SHL AX, CL
    SHR AL, CL  ; AH 此时为高四位 AL 为低四位
    
    MOV BX, OFFSET TABLE
    XLAT ; AL = ((BX) + (AL))
    MOV ES:[160*12+2*40 + 2], AL
    MOV AL, AH
    XLAT
    MOV ES:[160*12+2*40], AL
    
    POP CX
    POP BX
    POP AX 
    RET                           
    
CODE ENDS
END START