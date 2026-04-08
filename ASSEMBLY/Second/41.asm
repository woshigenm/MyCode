ASSUME CS:CODE, DS:DATA

ARRAYS_SIZES EQU 45

DATA SEGMENT
	ARRAYS DW 01, 00, 01, 00
		   DW 2 * (ARRAYS_SIZES - 2) DUP(0)
	BUFFER DW 256 DUP(0)   ; 字符串缓冲区（128个零初始化）
DATA ENDS

CODE SEGMENT
START:
	MOV AX, DATA
	MOV DS, AX
	
	LEA SI, DS:[ARRAYS]
	
	MOV CX, ARRAYS_SIZES - 2
MAIN_LOOP:
		MOV DX, DS:[SI + 2]
		MOV AX, DS:[SI]
		
		ADD AX, DS:[SI + 4]
		ADC DX, DS:[SI + 6]

        MOV DS:[SI + 10], DX
        MOV DS:[SI + 8], AX
		
		ADD SI, 4H 
	LOOP MAIN_LOOP
	
	CALL CLEAR_SCREEN

	CALL CONVERT         ; 将排序后的数组转换为字符串
	
	MOV BX, 0            ; 设置显存起始位置为0
	CALL PRINT           ; 打印转换后的字符串
	
    MOV AX, 4C00H
    INT 21H

; ===== 打印缓冲区内容到屏幕 ===== 
PRINT:
    PUSH AX              ; 保存寄存器
    PUSH SI
    PUSH ES
    PUSH BX
    
    MOV AX, 0B800H       ; 显存段地址
    MOV ES, AX            ; ES指向显存
    
    MOV AH, 07H           ; 字符属性：浅灰底黑字
    LEA SI, DS:[BUFFER]   ; SI指向缓冲区起始位置
    
PRINT_LOOP:
    MOV AL, DS:[SI]       ; 读取缓冲区中的字符
    CMP AL, 0H            ; 检查是否结束符（NULL）
    JE PRINT_OVER         ; 遇到结束符则结束打印

    MOV ES:[BX], AX       ; 写入显存（字符+属性）
    ADD BX, 2             ; 移动到下一个显存位置（每个字符2字节）
    INC SI                ; 移动到缓冲区下一个字符
    JMP SHORT PRINT_LOOP  ; 继续打印

PRINT_OVER:
    POP BX
    POP ES
    POP SI
    POP AX
    RET

; ===== 将数值数组转换为字符串 =====
CONVERT:
    PUSH AX              ; 保存寄存器
    PUSH CX
    PUSH DX
    PUSH SI
    PUSH DI

    MOV SI, 0            ; SI = 数组偏移（从0开始）
    LEA DI, DS:[BUFFER]   ; DI = 缓冲区起始位置
    MOV BYTE PTR DS:[DI], 0 ; 缓冲区初始为NULL（安全措施）
    
	MOV CX, ARRAYS_SIZES  ; 循环计数器（10个元素）
CONVERT_LOOP:
    ; 读取当前数组元素（32位）
    MOV AX, DS:[SI]       ; 低16位
    MOV DX, DS:[SI + 2]   ; 高16位

    PUSH CX               ; 保存外部循环计数器
    
    ; ===== 内部循环（数值转字符串） =====
    CONVERT_INNER_LOOP:
        MOV CX, 10        ; 设置除数为10
        CALL DIVDW        ; 执行32位除法（DX:AX / 10）
        
        ADD CL, 30H       ; 余数转换为ASCII字符（0-9 → '0'-'9'）
        MOV DS:[DI], CL   ; 存储字符到缓冲区
        INC DI            ; 移动到缓冲区下一个位置
        
        ; 检查商是否为0
        CMP AX, 0H        ; 检查低16位
        JNE CONVERT_INNER_LOOP
        CMP DX, 0H        ; 检查高16位
        JNE CONVERT_INNER_LOOP
    
    POP CX                ; 恢复外部循环计数器

    MOV BYTE PTR DS:[DI], ' ' ; 数字后添加空格分隔符
    INC DI                ; 移动到缓冲区下一个位置

    ADD SI, 4             ; 移动到数组下一个元素（4字节）
    LOOP CONVERT_LOOP      ; 继续转换下一个元素

    MOV BYTE PTR DS:[DI - 1], 0 ; 将最后一个空格设为结束符
    CALL REVERT           ; 反转字符串（因为转换结果是逆序的）

    POP DI                ; 恢复寄存器
    POP SI
    POP DX
    POP CX
    POP AX
    RET

; ===== 反转字符串中的每个数字 =====
REVERT:
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH SI
    PUSH DI

    LEA SI, BUFFER       ; SI -> 开始扫描缓冲区

NEXT_NUMBER:
    MOV DI, SI           ; DI = 当前数字起始位置

FIND_SPACE:
    MOV AL, [DI]         ; 读取当前字符
    CMP AL, ' '          ; 检查是否为空格
    JE  REVERSE_CURRENT  ; 找到空格，数字结束
    CMP AL, 0            ; 检查是否为结束符
    JE  REVERSE_CURRENT_LAST  ; 如果是结束符，进入最后数字翻转
    INC DI               ; 移动到下一个字符
    JMP FIND_SPACE

REVERSE_CURRENT:
    MOV BX, DI           ; BX = 空格位置
    MOV CX, BX           ; 计算数字长度
    SUB CX, SI           ; CX = 当前数字长度
    SHR CX, 1            ; CX = 需要交换的次数（对折）
    DEC BX
REVERSE_LOOP:
    JCXZ SKIP_REVERSE    ; 如果 CX = 0 就跳过
    MOV AL, [SI]         ; 获取开头字符
    MOV AH, [BX]         ; 获取结尾字符
    MOV [SI], AH         ; 交换开头和结尾字符
    MOV [BX], AL
    INC SI               ; 移动到下一个开头字符
    DEC BX               ; 移动到下一个结尾字符
    LOOP REVERSE_LOOP    ; 继续交换

SKIP_REVERSE:
    ; 移动 SI 到下一个数字的开头（跳过空格）
    MOV SI, DI
    INC SI
    JMP NEXT_NUMBER

REVERSE_CURRENT_LAST:
    MOV BX, DI           ; BX = 结束符前的位置
    MOV CX, BX           ; 计算数字长度
    SUB CX, SI           ; CX = 当前数字长度
    SHR CX, 1            ; CX = 需要交换的次数（对折）
    DEC BX
REVERSE_LAST_LOOP:
    JCXZ DONE_REVERSE    ; 如果没有字符需要交换，则跳过
    MOV AL, [SI]         ; 获取开头字符
    MOV AH, [BX]         ; 获取结尾字符
    MOV [SI], AH         ; 交换开头和结尾字符
    MOV [BX], AL
    INC SI               ; 移动到下一个开头字符
    DEC BX               ; 移动到下一个结尾字符
    LOOP REVERSE_LAST_LOOP
	
DONE_REVERSE:
    POP DI
    POP SI
    POP CX
    POP BX
    POP AX
    RET


; ===== 32位除法（DX:AX除以CX） =====
DIVDW:
    PUSH BX              ; 保存寄存器
    PUSH AX

    MOV AX, DX           ; 高16位移动到AX
    MOV DX, 0H           ; 高位扩展为0
    DIV CX               ; DX:AX / CX (商AX, 余数DX)

    MOV BX, AX           ; 保存高16位的商
    
    POP AX               ; 恢复低16位
    DIV CX               ; DX:AX / CX (商AX, 余数DX)

    MOV CX, DX           ; 余数放入CX（低位余数）
    MOV DX, BX           ; 高16位的商放入DX

    POP BX
    RET

; ===== 清屏功能 =====
CLEAR_SCREEN:
    MOV AX, 0600H       ; AH=06H（滚屏），AL=0（清屏）
    MOV BH, 07H         ; 属性：黑底白字
    XOR CX, CX          ; 左上角位置(0,0)
    MOV DX, 184FH       ; 右下角位置(24,79)
    INT 10H             ; 调用BIOS视频中断
    RET
	
CODE ENDS
END START