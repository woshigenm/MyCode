ASSUME CS:CODE, SS:STACK          ; 假定段寄存器对应段
MAX EQU 128                       ; 最大长度128
LINES EQU 18                      ; 行数18

; ===== 数据段A =====
DATA_A SEGMENT
    DW 0,0,1,0                   ; 初始数据
    DW 2 * (MAX - 2) DUP(0)      ; 初始化剩余空间为0
    BUFFER DW 128 DUP(0)         ; 用于存储转换后的字符串（缓冲区）
    BUFFER_LENGTH DW 0           ; 缓冲区长度
DATA_A ENDS

; ===== 数据段B =====
DATA_B SEGMENT
    DW 2*MAX DUP(0)              ; 数据区，用于中间存储
DATA_B ENDS

; ===== 堆栈段 =====
STACK SEGMENT
    DB 128 DUP(0)                ; 堆栈区，128字节
STACK ENDS

; ===== 代码段 =====
CODE SEGMENT
START:
    MOV AX, STACK                ; 初始化堆栈段
    MOV SS, AX
    MOV SP, 128                  ; 堆栈指针初始值128

    MOV AX, DATA_A               ; 初始化数据段
    MOV DS, AX

    MOV AX, DATA_B               ; 初始化附加段
    MOV ES, AX

    CALL CLEAR_SCREEN            ; 清屏

    MOV CX, 1                    ; 行号，初始为1
    MOV BX, 40                   ; 文本模式下的偏移量

MAIN_LOOP:                       ; 主循环标签
    MOV SI, 4H                   ; 偏移量（指向数据起始）

    CALL CONVERT                 ; 把数值转换成字符串并保存到BUFFER

    CALL PRINT                   ; 显示BUFFER中的内容
    ADD BX, 160                  ; 下一行位置（每行80字符，每字符2字节）

    PUSH CX
    INC CX
    PUSH CX
    MAIN_INNER_LOOP:             ; 行内循环
            MOV AX, DS:[SI - 4]     ; AX = 前一元素（前两项）
            MOV DX, DS:[SI  - 2]    ; DX = 前一元素（后一项）

            ADD AX, DS:[SI]         ; AX += 当前元素
            ADD DX, DS:[SI + 2]     ; DX += 当前元素

            MOV ES:[SI], AX         ; 结果存入B区
            MOV ES:[SI + 2], DX

            ADD SI, 4               ; 指向下一个元素（2个字）
        LOOP MAIN_INNER_LOOP
        POP CX
        CALL COPYBTOA               ; B区结果复制回A区
    POP CX

    INC CX
    CMP CX, LINES                   ; 判断是否达到指定行数
    JBE MAIN_LOOP                   ; 未到则继续

    MOV AX, 4C00H                   ; 退出程序
    INT 21H

; ========== 打印BUFFER ========== 
PRINT:
    PUSH AX
    PUSH SI
    PUSH ES
    PUSH BX
    MOV AX, 0B800H                  ; 显存段基址
    MOV ES, AX

    MOV AH, 07H                     ; 字符属性（白底黑字）
    LEA SI, DS:[BUFFER]             ; SI指向BUFFER
PRINT_LOOP:
        MOV AL, DS:[SI]             ; 取出一个字符
        CMP AL, 0H                  ; 判断是否为字符串结束
        JE PRINT_OVER

        MOV ES:[BX], AX             ; 显示在屏幕指定位置
        ADD BX, 2                   ; 下一个字符
        INC SI                      ; 下一个字符
    JMP SHORT PRINT_LOOP

PRINT_OVER:
    POP BX
    SUB BX, 2
    POP ES
    POP SI
    POP AX
    RET

; ========== 数值转字符串 ==========
CONVERT:
    PUSH AX
    PUSH CX
    PUSH DX
    PUSH SI
    PUSH DI

    MOV SI, 4                       ; 数据起始偏移
    LEA DI, DS:[BUFFER]             ; DI指向BUFFER
    MOV BYTE PTR DS:[DI], 0         ; 先写个0，防止意外
CONVERT_LOOP:
        MOV AX, DS:[SI]             ; 取数据低16位
        MOV DX, DS:[SI + 2]         ; 取数据高16位

        CALL GET_LENGTH             ; 计算十进制长度

        PUSH CX
        MOV CX, DS:[BUFFER_LENGTH]  ; 获取长度
        CONVERT_INNER_LOOP:
            MOV CX, 10              ; 除以10
            CALL DIVDW              ; 双字除法，余数在CL

            ADD CL, 30H             ; 转换为字符
            MOV DS:[DI], CL         ; 写入缓冲区

            INC DI
            CMP AX, 0H
            JNE CONVERT_INNER_LOOP
            CMP DX, 0H
            JNE CONVERT_INNER_LOOP
        POP CX

        MOV BYTE PTR DS:[DI], ' '   ; 数字间加空格
        INC DI

        ADD SI, 4                   ; 下一个数
    LOOP CONVERT_LOOP

    MOV BYTE PTR DS:[DI - 1], 0     ; 字符串结束
    CALL REVERT                     ; 字符逆序

    POP DI
    POP SI
    POP DX
    POP CX
    POP AX
    RET

; ========== 字符串逆序 ==========
REVERT:
    PUSH AX
    PUSH CX
    PUSH SI
    PUSH DI

    LEA SI, DS:[BUFFER]             ; SI指向BUFFER
    CALL CALC                       ; DI指向BUFFER末尾

    MOV CX, DI                      ; 计算长度
    DEC DI
    SUB CX, SI
    SHR CX, 1                       ; 只需对折交换
    REVERT_LOOP:
            JCXZ REVERT_OVER        ; 长度为0则退出

            MOV AH, DS:[SI]
            MOV AL, DS:[DI]

            MOV DS:[DI], AH
            MOV DS:[SI], AL

            INC SI
            DEC DI
        LOOP REVERT_LOOP

REVERT_OVER:
    POP DI
    POP SI
    POP CX
    POP AX
    RET

; ========== 计算BUFFER长度 ==========
CALC:
    LEA DI, DS:[BUFFER]
CALC_LOOP:
        INC DI
    CMP BYTE PTR DS:[DI], 0
    JNE CALC_LOOP
    RET

; ========== 32位除法 ==========
DIVDW:
    PUSH BX
    PUSH AX

    MOV AX, DX                     ; 高16位到AX
    MOV DX, 0H
    DIV CX                        ; 除以CX，商在AX，余在DX

    MOV BX, AX                    ; 暂存高位商

    POP AX
    DIV CX                        ; 除以CX，商在AX，余在DX

    MOV CX, DX                    ; 低位余数
    MOV DX, BX                    ; 高位商

    POP BX
    RET

; ========== 计算十进制长度 ==========
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

; ========== B区复制到A区 ==========
COPYBTOA:
    PUSH AX
    PUSH CX
    PUSH DS
    PUSH SI
    PUSH ES
    PUSH DI

    MOV AX, DATA_B
    MOV DS, AX
    MOV AX, DATA_A
    MOV ES, AX

    MOV SI, 4
    MOV DI, SI

    CLD
    SHL CX, 1                     ; 乘2，双字单位
    REP MOVSW                     ; 拷贝数据

    POP DI
    POP ES
    POP SI
    POP DS
    POP CX
    POP AX
    RET

; ========== 清屏 ==========
CLEAR_SCREEN:
    MOV AX, 0600H      ; AH=06H，AL=0，滚屏/清屏
    MOV BH, 07H        ; 白底黑字
    XOR CX, CX         ; 左上角(0,0)
    MOV DX, 184FH      ; 右下角(24,79)
    INT 10H
    RET

CODE ENDS
END START
