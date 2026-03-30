ASSUME CS:CODE, DS:DATA, SS:STACK

STACK SEGMENT
    DB 128 DUP(0)
STACK ENDS

DATA SEGMENT
    DB 128 DUP(0)
DATA ENDS

CODE SEGMENT
START:
    MOV AX, STACK
    MOV SS, AX
    MOV SP, 128
     
    MOV AX, DATA
    MOV DS, AX
    
    XOR SI, SI
    CALL SCANF
    
    MOV AH, 03h      ; BIOS 获取光标位置
    MOV BH, 0        ; 视频页 0
    INT 10h
    
    INC DH
    MOV AH, 02H
    INT 10H 
    
    MOV AH, 9
    XOR DX, DX
    INT 21H
       
    MOV AX, 4C00H
    INT 21H

;DS:SI 为字符串存储位置 字符串以零结尾
SCANF:
    PUSH ES
    PUSH AX

    MOV AX, 0B800h
    MOV ES, AX

    XOR SI, SI
    CALL GET_CURSOR_POS  ; 获取当前光标位置
    MOV CX, BX           ; 保存输入起始位置

MAIN_LOOP:
    XOR AH, AH
    INT 16h              ; 等待按键

    CMP AH, 1Ch
    JE  SCANF_OVER       ; Enter
    
    CMP AH, 0Eh
    JE  HANDLE_BACKSPACE ; Backspace
    
    CMP SI, 127
    JE SCANF_OVER
    
    CALL PUT_CHAR        ; 普通字符
    JMP MAIN_LOOP

HANDLE_BACKSPACE:
    CMP BX, CX
    JE  MAIN_LOOP
    SUB BX, 2
    DEC SI
    MOV BYTE PTR ES:[BX], ' '
    JMP MAIN_LOOP

SCANF_OVER:
    MOV BYTE PTR DS:[SI], '$'

    POP AX
    POP ES
    RET

; 返回值：BX = 光标当前位置对应的显存偏移
GET_CURSOR_POS:
    PUSH AX
    PUSH DX

    MOV AH, 03h      ; BIOS 获取光标位置
    MOV BH, 0        ; 视频页 0
    INT 10h

    MOV AL, 160      ; 每行 80 列 * 2 字节 = 160
    MUL DH           ; AX = 行号 * 160
    MOV BX, AX

    MOV AL, DL       ; 列号
    ADD AL, AL       ; *2 (每列占2字节)
    XOR AH, AH
    ADD BX, AX       ; BX = 行偏移 + 列偏移

    POP DX
    POP AX
    RET

PUT_CHAR:
    MOV ES:[BX], AL   ; 显存
    MOV DS:[SI], AL   ; 缓冲区
    ADD BX, 2
    INC SI
    RET

CODE ENDS
END START