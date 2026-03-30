ASSUME CS:CODE,SS:STACK

STACK SEGMENT
    DW 128 DUP(0)
STACK ENDS

CODE SEGMENT
START:
    MOV AX, STACK
    MOV SS, AX
    MOV SP, 256
    
    CALL SYSTEM_TOOLS
   
    MOV AX, 4C00H
    INT 21H

; AL 功能号
SYSTEM_TOOLS:
    JMP SHORT SET
    CLEAR DW CLEAR_SCREEN
    PRINT_HELLO  DW PRINT_H
    TABLE DW RESET,STRATUP,CLOCK,SETCLOCK
    ERROR DW ERROR_HANDLE
SET:
    PUSH BX
    
    ; CALL WORD PTR CS:[CLEAR]
    
    CALL WORD PTR CS:[PRINT_HELLO]
    
    MOV AH, 0
    INT 16H
    SUB AL, 30H
    
    CMP AL, 1
    JB RE
    CMP AL, 4
    JA RE
    
    DEC AL
    
    SHL AL, 1
    XOR AH, AH
    
    MOV BX, AX
    
    CALL WORD PTR CS:TABLE[BX]
    JMP SHORT SET_OVER 
RE:               
    CALL WORD PTR CS:[ERROR]
    JMP SHORT SET_OVER 
SET_OVER:    
    POP BX
    RET

RESET:
    JMP SHORT RESET_S  
    RESET_DATA DW 0H, 0FFFFH
RESET_S: 
    JMP DWORD PTR CS:[RESET_DATA]
    RET

STRATUP:              
    JMP SHORT STARTUP_S 
    CHS_TABLE DW INT7C
    CHS_ADDR DW 0, 7C00H, 0
STARTUP_S:   
    MOV DX, CS:[CHS_ADDR]
    MOV ES, DX 
    MOV DX, 0H
    MOV BX, CS:[CHS_ADDR + 2]
    
    CALL WORD PTR CS:[CHS_TABLE]
    
    JMP DWORD PTR CS:[CHS_ADDR + 2] 
    RET 

CLOCK:
    JMP SHORT CLOCK_SET
    INSTALLED_INT9 DB 0 ; 0 为未安装 1 为已安装
    INTSTALL DW INNSTALL_INT9H
    TEMP_INT9 DW 0,0
    DELAY_S DW DELAY
    CLOCK_STRING DB 'yyyy/mm/dd HH:MM:SS',0
    CLOCK_OFFSET DW  9,8,7,4,2,0
    BCD_TOOL DW BCD
CLOCK_SET:
    PUSH AX
    PUSH ES
    PUSH DI
    
    MOV AX, 0
    MOV ES, AX 
    
    PUSH ES:[4 * 9H]
    POP CS:[TEMP_INT9] ; 保存向量表
    PUSH ES:[4 * 9H + 2]
    POP CS:[TEMP_INT9] 
     
    ; CALL WORD PTR CS:[DELAY_S]
    CMP BYTE PTR CS:[INSTALLED_INT9], 0
    JNE CONTINUE_SET ; 已安装
    MOV CS:[INSTALLED_INT9], 1
    CALL WORD PTR CS:[INTSTALL]

CONTINUE_SET:
    MOV AX, 0B800H
    MOV ES, AX
    
    MOV AL, 32H
    OUT 70H, AL
    IN  AL, 71H
        
    CALL WORD PTR CS:[BCD_TOOL]
    
    MOV BX, OFFSET CLOCK_STRING

    MOV CS:[BX], AX

    CLI
    PUSH CS:[TEMP_INT9] 
    POP ES:[4 * 9H] ; 恢复向量表
    PUSH CS:[TEMP_INT9 + 2]
    POP ES:[4 * 9H + 2]
    STI   
    
    POP DI
    POP ES
    POP AX
    RET

SETCLOCK:
    NOP
    RET

ERROR_HANDLE:
    JMP SHORT ERROR_S
    ERROR_STRING DB 'INVAILD INPUT. PLEASE INPUT 1-4', 0
ERROR_S:
    PUSH DS
    PUSH SI   
    PUSH AX
    PUSH CX
    PUSH DX
    
    MOV AX, CS
    MOV DS, AX
    MOV CL, 4
    MOV DX, 000H

    MOV SI, OFFSET ERROR_STRING  
    CALL PRINT
    
    POP DX
    POP CX
    POP AX
    POP SI
    POP DS
    RET 

; DH 行 DL 列 CL 颜色 DS:SI 字符串地址
PRINT:
    PUSH AX
    PUSH DX
    PUSH BX
    
    MOV AX, 0B800H
    MOV ES, AX
    
    MOV AL, 160
    MUL DH
    
    MOV BX, AX
    
    SHL DL, 1
    XOR DH, DH
    
    ADD BX, DX
    
    MOV DH, CL
PRINT_LOOP:
        MOV DL, DS:[SI]
        CMP DL, 0
        JE PRINT_OVER
        MOV ES:[BX], DX
        ADD BX, 2
        INC SI 
    JMP SHORT PRINT_LOOP
PRINT_OVER:
    POP BX
    POP DX
    POP AX
    RET

PRINT_H:
    JMP SHORT PRINT_H_S 
    STRING1 DB '1) RETSET PC',0
    STRING2 DB '2) START SYSTEM',0
    STRING3 DB '3) CLOCK',0
    STRING4 DB '4) SET CLOCK',0
    STRING5 DB 'PLEASE INTPUT(1-4)',0
    STRING_OFFSET DW STRING1, STRING2, STRING3, STRING4, STRING5    
PRINT_H_S:
    PUSH CX
    PUSH DS
    PUSH SI
    PUSH BX
    PUSH DX
    
    MOV AX, CS
    MOV DS, AX
; DH 行 DL 列 CL 颜色 DS:SI 字符串地址
    XOR BX, BX
    MOV DX, 0000H
    MOV CX, 5
PRINT_H_LOOP:
        PUSH CX
        
        MOV SI, CS:[STRING_OFFSET + BX] 
        MOV CL, 2    
        CALL PRINT
        INC DH

        ADD BX, 2
        POP CX    
    LOOP PRINT_H_LOOP 
    
    POP DX
    POP BX
    POP SI
    POP DS
    POP CX
    RET

CLEAR_SCREEN:
    PUSH AX  
    PUSH CX
    PUSH ES
    PUSH DI
    
    MOV AX, 0B800H
    MOV ES, AX
    
    XOR DI, DI
    
    MOV AX, 0007H
    
    CLD
     
    MOV CX, 2000
    REP STOSW
    
    POP DI
    POP ES
    POP CX
    POP AX
    RET

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
    RET

DELAY:
    PUSH DX
    PUSH AX
    
    MOV AX, 0FFFFH
    MOV DX, 0FFFFH
    
    CLC
DELAY_LOOP:
    SUB AX, 1
    SBB DX, 0
    CMP AX, 0
    JNE DELAY_LOOP
    CMP DX, 0
    JNE DELAY_LOOP    
    
    POP AX
    POP DX
    RET

INNSTALL_INT9H:
    PUSH AX
    PUSH DS
    PUSH ES
    PUSH DI
    PUSH CX
    PUSH SI

    MOV AX, CS
    MOV DS, AX
    XOR SI, SI
    
    MOV AX, 0
    MOV ES, AX
    MOV DI, 0200H
    
    CLD
    
    MOV CX, OFFSET INT9H_END - OFFSET INT9H
    REP MOVSB       
    
INNSTALL_INT9H_OVER:    
    POP SI
    POP CX
    POP DI
    POP ES
    POP ES
    POP AX
    RET

INT9H:
    JMP SHORT INT9H_S 
    SOURCE_INT9H DW 0,0
INT9H_S:
    PUSH AX
    PUSH DS
    
    MOV AX, 0
    MOV DS, AX

    PUSH DS:[4 * 9H]
    POP CS:[SOURCE_INT9H]
    PUSH DS:[4 * 9H + 2]
    POP CS:[SOURCE_INT9H + 2]
    
    PUSHF 
    CALL DWORD PTR CS:[SOURCE_INT9H]
    
    IRET

INT9H_END:
    NOP

; AL 为 8 位 BCD， 结果转成字符存储在 AH 和 AL 中
BCD:
    PUSH CX
    
    MOV CL, 4
    SHL AX, CL
    SHR AL, CL
    
    ADD AH, 30H
    ADD AL, 30H 
    
    XCHG AH, AL
    
    POP CX    
    RET
        
CODE ENDS
END START