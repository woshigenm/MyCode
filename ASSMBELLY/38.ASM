ASSUME CS:CODE

PRIME_TABLE_SIZE    EQU 0FFH           ; 素数表最大范围 (160)
PRIME_TABLE_START   EQU 02H            ; 从2开始判断素数

DATA SEGMENT
    PRIME_TABLE         DB PRIME_TABLE_SIZE DUP(0)   ; 素数筛表
                        DB 0                        ; 填充字节，对齐
    PRIME_BUFFER        DB 8 DUP(0)                  ; 转换输出用缓冲
    BUFFER_LENGTH       DW 0                         ; 缓冲长度
DATA ENDS

STACK SEGMENT
    DW   128  DUP(0)                                ; 堆栈区
STACK ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX                                      ; 初始化数据段
    
    MOV AX, STACK
    MOV SS, AX
    MOV SP, 256                                     ; 堆栈指针
    
    CALL PRIME                                      ; 筛素数
    
    CALL CLEAR_SCREEN                               ; 清屏
    
    CALL PRINT_PRIME                                ; 打印素数
    
    MOV AX, 4C00H
    INT 21H                                         ; 程序退出

; =======================
; 打印素数表
; =======================
PRINT_PRIME:
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH SI
    PUSH ES
    PUSH DI
    
    MOV SI, PRIME_TABLE_START                       ; 从2号下标开始
    
    MOV BX, 0                                       ; 屏幕打印偏移
PRINT_PRIME_LOOP:
        CMP BYTE PTR DS:[SI], 0H                    ; 如果表中是0，说明是素数
        JNE PRINT_PRIME_LOOP_END                    ; 不是素数，跳过
        
        CMP SI, PRIME_TABLE_SIZE                    ; 到头没
        JE PRINT_PRIME_LOOP_OVER                    ; 结束
        
        MOV DX, 0
        MOV AX, SI                                  ; SI放入AX，准备转换
        CALL GET_LENGTH                             ; 求出数字长度
        
        MOV CX, DS:[BUFFER_LENGTH]                  ; 取长度
        LEA DI, DS:[PRIME_BUFFER]
        ADD DI, CX
        DEC DI                                      ; DI指向数字末尾
        
        MOV AX, SI                                  ; 要转换的数字
        PRIME_INNER_LOOP:
                PUSH CX
                
                MOV DX, 0
                MOV CX, 10
                CALL DIVDW                          ; 除10，结果在AX, 余数在CL
                
                ADD CX, 30H
                MOV DS:[DI], CL                     ; 存入字符
                
                DEC DI
                POP CX
            LOOP PRIME_INNER_LOOP                   ; 一位一位存
        
        CALL PRINT                                  ; 输出该素数
        
PRINT_PRIME_LOOP_END:
        INC SI                                      ; 下一个数
    JMP SHORT PRINT_PRIME_LOOP

PRINT_PRIME_LOOP_OVER:    
    POP DI
    POP ES
    POP SI
    POP CX
    POP BX
    POP AX
    RET

; =======================
; 打印缓冲区内容到屏幕
; =======================
PRINT:
    PUSH AX
    PUSH ES
    PUSH SI
    
    MOV AX, 0B800H
    MOV ES, AX                                      ; 显存段
    
    LEA SI, DS:[PRIME_BUFFER]
    
    MOV AH, 07H                                     ; 白底黑字
PRINT_LOOP:
        MOV AL, DS:[SI]                             ; 取字符
        CMP AL, 0H
        JE PRINT_OVER                               ; 结束
        
        MOV ES:[BX], AX                             ; 显存写字符
        
        ADD BX, 2                                   ; 下一个字符（每个字符2字节）
        INC SI                                      ; 下一个字符

    JMP SHORT PRINT_LOOP
    
PRINT_OVER:
    
    ADD BX, 2                                       ; 打印后移一位空格
    
    POP SI
    POP ES    
    POP AX
    RET
    
; =======================
; 素数筛法
; =======================
PRIME:
    PUSH AX
    PUSH DX
    PUSH DI
    PUSH SI
    
    MOV SI, PRIME_TABLE_START                       ; SI = 2
PRIME_LOOP:
        MOV AX, SI
        MUL AX                                      ; AX = SI * SI
        
        CMP AX, PRIME_TABLE_SIZE
        JAE  PRIME_LOOP_OVER                        ; 超出表范围
        
        CMP BYTE PTR DS:[SI], 0                     ; 若已被标记跳过
        JNE PRIME_LOOP_END
        
        MOV DI, AX                                  ; 从SI*SI 开始筛
    INNER_LOOP:
            CMP DI, PRIME_TABLE_SIZE
            JAE  PRIME_LOOP_END                     ; 超出表范围
            
            INC BYTE PTR DS:[DI]                    ; 标记为非素数
            
            ADD DI, SI                             ; DI += SI，下一个倍数
            
        JMP SHORT INNER_LOOP                        ; 循环

PRIME_LOOP_END:    
        INC SI                                      ; 下一个数
    JMP SHORT PRIME_LOOP

PRIME_LOOP_OVER:    
    POP SI
    POP DI
    POP DX
    POP AX
    RET

; =======================
; 32位无符号除法
; 输入: DX:AX / CX
; 输出: DX:AX = 商, CX=余数
; =======================
DIVDW:
    PUSH BX
    
    PUSH AX ; 低位
    
    MOV AX, DX
    MOV DX, 0H
    DIV CX                                      ; 高位除法
    ; AX = 商, DX = 余数
    
    MOV BX, AX                                  ; 商存BX
    
    POP AX                                      ; 恢复低位
    DIV CX
    ; AX = 商, DX = 余数
   
    MOV CX, DX                                  ; 余数给CX
    MOV DX, BX                                  ; 高位商给DX
    
    POP BX
    RET
    
; =======================
; 求十进制长度
; DX:AX
; 返回 DS:[BUFFER_LENGTH]
; =======================
GET_LENGTH:
    PUSH AX
    PUSH CX
    PUSH DX
    
    MOV WORD PTR DS:[BUFFER_LENGTH], 0
LENGTH_LOOP:
        MOV CX, 10
        
        CALL DIVDW
        
        INC WORD PTR DS:[BUFFER_LENGTH]
        
        CMP AX, 0H
        JNE LENGTH_LOOP
        CMP DX, 0H
        JNE LENGTH_LOOP
        
    POP DX
    POP CX
    POP AX
    RET

; =======================
; 清屏
; =======================
CLEAR_SCREEN:
    MOV AX, 0600H      ; AH = 06H: SCROLL UP WINDOW, AL = 0 (CLEAR ENTIRE WINDOW)
    MOV BH, 07H        ; 白底黑字
    XOR CX, CX         ; 左上角 (0,0)
    MOV DX, 184FH      ; 右下角 (24,79)
    INT 10H
    RET    
    
CODE ENDS
END START