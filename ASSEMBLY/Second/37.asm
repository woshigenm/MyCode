ASSUME CS:CODE,SS:STACK,DS:DATA

STACK SEGMENT
    DW 128 DUP(0)
STACK ENDS

DATA SEGMENT
    ;DB 0F8H
    ;DB 511 DUP(0)
     DB 512 DUP(0)
DATA ENDS

CODE SEGMENT
START:
    MOV AX, STACK
    MOV SS, AX
    MOV SP, 256
    
    MOV AX, 0
    MOV ES, AX
    MOV DI, 200H
    
    MOV AX, CS
    MOV DS, AX
    MOV SI, OFFSET INT7C
    
    CLD
    
    MOV CX, OFFSET INT7C_E - OFFSET INT7C
    
    REP MOVSB

    CLI
    MOV WORD PTR ES:[4 * 7CH], 200H
    MOV WORD PTR ES:[4 * 7CH + 2], 0H
    STI  
    
    MOV AX, DATA 
    MOV ES, AX
    XOR BX, BX
    
    MOV AH, 0H
    MOV DX, 01H
    
    INT 7CH
    
    MOV AX, 4C00H
    INT 21H

INT7C: 
    JMP SHORT INT7C_S
    NUMBER DW 1440
    NUM DW 18
INT7C_S:
    PUSH DX
    PUSH CX

    PUSH AX

    MOV AX, DX
    XOR DX, DX      ; AX = 面号 DH
    DIV CS:[NUMBER] ; AX = INT(逻辑扇区号/1440) DX = REG(逻辑扇区号/1440)
    
    PUSH AX

    MOV AX, DX
    
    XOR DX, DX       ; AX = 磁道号 CH DX = 扇区号 CL
    DIV CS:[NUM] ;   AX = INT(REG(逻辑扇区号/1440)/18) DX = REG((REG(逻辑扇区号/1440)/18))
    
    MOV CH, AL
    INC DL
    MOV CL, DL
    
    POP AX 
    MOV DH, AL
    MOV DL, 0H
    
    MOV AH, 00H     ; 功能号 00H：重置磁盘系统
    INT 13H         ; 调用 BIOS 中断

    POP AX
    
    MOV AL, 1H
    
    CMP AH, 1H
    JA OVER
    ADD AH, 2
    INT 13H
OVER:   
    POP CX
    POP DX
    IRET

INT7C_E:
    NOP
                
CODE ENDS
END START