ASSUME CS:CODE,SS:STACK

STACK SEGMENT
   DW 128 DUP(0)
STACK ENDS

DATA SEGMENT
    STRING DW 128 DUP(0)
    LENGTHS DW 0
DATA ENDS

CODE SEGMENT
START:
    MOV AX, STACK
    MOV SS, AX
    MOV SP, 256
    
    MOV AX, DATA
    MOV DS, AX
    XOR SI, SI

    MOV AH, 03h      ; BIOS 获取光标位置
    MOV BH, 0        ; 视频页 0
    INT 10h
S:  
    MOV AH, 0
    INT 16H
    CMP AL, 20H
    JB OVER 
    CMP AH, 0EH
    JE BACK
    CMP AH, 1CH
    JE OVER
    MOV AH, 0
    CALL CHARSTACK

    JMP SHORT S

BACK:
    MOV AH, 1
    CALL CHARSTACK    
    JMP SHORT S
    
OVER:
    MOV DS:[LENGTHS], SI
    MOV BYTE PTR DS:[SI], '$' 

    INC DH
    MOV AH, 02H
    INT 10H 
    
    MOV AH, 9
    XOR DX, DX
    INT 21H
        
    MOV AX, 4C00H
    INT 21H
; AH 功能号 AL 入栈字符或返回字符 DH:DL 显示行列
; DS:SI 存储字符串位置
CHARSTACK:
    JMP SHORT CHARSTACK_START
    TABLE DW CHARPUSH, CHARPOP 
CHARSTACK_START:
    PUSH BX
    
    CMP AH, 2
    JA OVEER_CHAR             
    XOR BX, BX
    MOV BL, AH
    SHL BX, 1
    
    CALL WORD PTR CS:TABLE[BX]
OVEER_CHAR:    
    POP BX
    RET
; AL 入栈字符
CHARPUSH:
    MOV DS:[SI], AL
    CALL CHARSHOWS 
    INC SI
    RET
        
; AL 返回字符
CHARPOP:
    CMP SI, 0
    JE CHARPOP_OVER
    MOV AL, DS:[SI]
    DEC SI
    MOV BYTE PTR DS:[SI], 0
    CALL CHARSHOWS
CHARPOP_OVER:
    RET

CHARSHOWS:
    PUSH AX
    PUSH ES
    PUSH BX
    PUSH DX
    
    MOV AX, 0B800H
    MOV ES, AX
     
    XOR BX, BX
    
    MOV AL, 160
    MUL DH ; AX
    
    ADD BX, AX
    
    SHL DL, 1
    MOV DH, 0
    ADD BX, DX
    
    MOV AL, DS:[SI]         
    MOV DI, SI
    SHL DI, 1
    MOV ES:[BX + DI], AL

    POP DX
    POP BX
    POP ES
    POP AX
    RET
                
CODE ENDS
END START