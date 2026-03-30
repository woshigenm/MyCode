ASSUME CS:CODE,SS:STACK

STACK SEGMENT
    DB 16 DUP(0)
STACK ENDS

DATA SEGMENT
    DB 'yyyy/mm/dd HH:MM:SS','$'
    DW  9,8,7,4,2,0
DATA ENDS

CODE SEGMENT
START:
    MOV AX, STACK
    MOV SS, AX
    MOV SP, 16
    
    MOV AX, DATA
    MOV DS, AX
    
    MOV AL, 32h      ; 世纪寄存器
    OUT 70h, AL
    IN AL, 71h       ; AL=20h (20xx年)
    
    CALL BCD 
    
    MOV DS:[SI], AX
    
    ; CALL CLEAR_SCREEN

    MOV SI, 2 ; SI 访问字符串
    MOV DI, 20
    MOV CX, 7
LOOP_ALL:
    MOV AL, DS:[DI]
    OUT 70H, AL
    IN AL, 71H
        
    CALL BCD
    
    MOV DS:[SI], AX
         
    ADD SI, 3
    ADD DI, 2
    LOOP LOOP_ALL
    
	MOV AH, 03h      ; BIOS 获取光标位置
    MOV BH, 0        ; 视频页 0
    INT 10h
    
    MOV AH, 02H		 ; 设置光标位置
    INT 10H 
	
    MOV AH, 9		 ; 	显示字符串DS:DX '$'为结束字符串 
    XOR DX, DX
    INT 21H    

    MOV AX, 04C00H
    INT 21H

; AL 为 8位 BCD， 结果转成字符存储在 AH 和 AL 中
BCD:
    PUSH CX
SPLIT:
    MOV CL, 4
    MOV AH, AL
	AND AL, 0Fh      ; 低位
	SHR AH, CL        ; 高位

	;ROR AX, CL
	;SHR AH, CL
    ;SHL AX, CL
    ;SHR AL, CL 
    
    XCHG AH, AL
     
    ADD AL, 30H
    ADD AH, 30H
    
    POP CX
    RET
    
CLEAR_SCREEN:
    PUSH ES      ; 保存关键寄存器
    PUSH AX
    PUSH CX
    PUSH DI
CLEAR:    
    MOV AX, 0B800H
    MOV ES, AX   ; 使用ES访问显存
    
    XOR DI, DI   ; 从显存开头开始
    
    MOV CX, 2000 
    
    MOV AX, 0720H  ; AH=属性, AL=字符
    
    CLD           ; 设置方向向前

    REP STOSW         ; ES:[DI]←AX, DI+2
    
    POP DI
    POP CX
    POP AX
    POP ES        ; 恢复原始ES
    RET
    
CODE ENDS
END START

