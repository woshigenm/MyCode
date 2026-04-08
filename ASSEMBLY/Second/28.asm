; 应用举例：在屏幕的第 12 行，显示 DATA 段中以 0 结尾的字符串。
ASSUME CS:CODE

DATA SEGMENT
  DB 'CONVERSATION!!!', 0
DATA ENDS

STACK SEGMENT
  DW 8 DUP(0)
STACK ENDS

CODE SEGMENT
  START:
    MOV AX, 0003h  ; AH=00h(设置模式), AL=03h(80×25彩色)
    INT 10h

    MOV AX, STACK
    MOV SS, AX
    MOV SP, 16
    
    MOV AX, 0
    MOV ES, AX
    
    MOV AX, CS
    MOV DS, AX
    
    MOV SI, OFFSET JMP_FAKE
    MOV DI, 200H
    
    CLD
     
    MOV CX, OFFSET JMP_FAKE_OVER  - OFFSET JMP_FAKE 
    
    REP MOVSB
    
    CLI
    MOV WORD PTR ES:[4 * 7CH + 2], 0
    MOV WORD PTR ES:[4 * 7CH], 200H
    STI
 
    MOV AX, DATA
    MOV DS, AX
    MOV SI, 0H
    MOV AX, 0B800H
    MOV ES, AX
    MOV DI, 12*160
    
  S:
    CMP BYTE PTR [SI], 0H
    JE OK
    MOV AL, DS:[SI]
    MOV ES:[DI], AL
    INC SI
    ADD DI, 2H
    MOV BX, OFFSET S - OFFSET OK
    INT 7CH

  OK:
    MOV AX, 4C00H
    INT 21H
    
JMP_FAKE:
    PUSH BP    ;                         SP
    MOV BP, SP ; STACK 00 00 00 00 00 00 BP BP IP IP CS CS FLAG FLAG 
    
    ADD [BP + 2], BX
    
    MOV SP, BP
    POP BP
    IRET
    
JMP_FAKE_OVER:
    NOP    
    
CODE ENDS
END START