ASSUME CS:CODE

DATA SEGMENT
    DB 10 DUP(0)    
DATA ENDS

CODE SEGMENT
START:
    MOV AX, 520
    MOV BX, DATA
    MOV DS, BX   
    MOV SI, 0
    CALL DTOC
        
    MOV DH, 3
    MOV DL, 3
    MOV CL, 2
    CALL SHOW_STR
    
    MOV AX, 04C00H
    INT 21H
    
DTOC:
    PUSH SI
CONVERT_LOOP_MAIN:
    MOV BX, 10
CONVERT_LOOP: 
    XOR DX, DX
    DIV BX
    
    ADD DL, 30H
    
    MOV DS:[SI], DL
    
    INC SI
    MOV CX, AX
    JCXZ CONVERT_END
    
    
    JMP SHORT CONVERT_LOOP
CONVERT_END:  
    MOV BYTE PTR DS:[SI], 0 
    
    MOV DI, SI
    
    MOV AX, DI
    MOV BL, 2
    DIV BL
    
    DEC DI 
    MOV SI, 0
    
    XOR CX, CX
    MOV CL, AL
    REVERSE_LOOP: 
        MOV AL, DS:[DI]
        MOV BL, DS:[SI]
        MOV DS:[DI], BL
        MOV DS:[SI], AL 
        
        INC SI
        DEC DI    
    LOOP REVERSE_LOOP
     
    POP SI
    RET
    
SHOW_STR:
    PUSH CX
    PUSH DX
    PUSH AX
      
    MOV AX, 0B800H
    MOV ES, AX 
    
    ; ¼ÆËãÐÐÆ«ÒÆÖµ
    MOV AL, 0A0H  
    MUL DH 
    
    MOV BX, AX
    
    ADD DL, DL
    
    XOR DH, DH
    MOV DI, DX
    
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
    POP AX
    POP DX
    POP CX     
    RET
        
DIVDW:       
    MOV BX, AX
    
    MOV AX, DX
    MOV DX, 0
    DIV CX
    ; AX=INT(H/N)   DX=REM(H/N)
    MOV SI, AX
    MOV AX, BX
    DIV CX
    ; AX=INT(REM(H/N)*1000H+L)   DX=REM(REM(H/N)*1000H+L)
    MOV CX, DX
    MOV DX, SI
    RET
            
CODE ENDS
END START