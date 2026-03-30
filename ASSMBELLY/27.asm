ASSUME CS:CODE

STACK SEGMENT
    DW 8 DUP(0)
STACK ENDS

CODE SEGMENT      
START:
    MOV AX, STACK
    MOV SS, AX
    MOV SP, 16

    MOV AX, CS
    MOV DS, AX
    
    MOV AX, 0     
    MOV ES, AX
    
    MOV SI, OFFSET FAKE_LOOP
    MOV DI, 200H
    
    MOV CX, OFFSET OVER_FAKE_LOOP - OFFSET FAKE_LOOP
    
    CLD
    
    REP MOVSB
    
    MOV WORD PTR ES:[4 * 7CH + 2], 0H 
    MOV WORD PTR ES:[4 * 7CH], 200H
    
    MOV AX, 0B800H    
    MOV ES, AX
    
    MOV DI, 12*160
    
    MOV BX, OFFSET PRINT - OFFSET FUCK
    MOV CX, 80
PRINT:
        MOV ES:[DI], '!'
        ADD DI, 2   
		INT 7CH
FUCK:
    NOP    
    
    MOV AX, 04C00H
    INT 21H

    
; CX = Ñ­»·´ÎÊý BX = Æ«ÒÆ   
FAKE_LOOP:
    PUSH BP    ;                         SP
    MOV BP, SP ; STACK 00 00 00 00 00 00 BP BP IP IP CS CS FLAG FLAG 
    DEC CX
    JCXZ OVER      
    ADD [BP + 2], BX
OVER:
    POP BP    
    IRET
    
OVER_FAKE_LOOP:
    NOP
     
CODE ENDS
END START