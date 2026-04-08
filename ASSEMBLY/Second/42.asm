ASSUME CS:CODE, DS:DATA

ARRAYS_SIZES  EQU   16
NEWLINE_SIZES EQU   4
ROWS          EQU   4
COLS          EQU   4
SPACE         EQU   4

DATA SEGMENT
	ARRAYS_OLD DD 0,1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE,0xF
	ARRAYS_NEW DW ARRAYS_SIZES * 2 DUP(0)
	BUFFER     DW 256 DUP(0)
DATA ENDS

CODE SEGMENT
START:
	MOV AX, DATA
	MOV DS, AX
	
    MOV CX, COLS
	XOR SI, SI ; ROW
MAIN_LOOP:
	XOR DI, DI ; COL
	MAIN_INNER_LOOP:
		MOV AX, SI
		XOR DX, DX
        MUL CX
		
		MOV BX, AX
		ADD BX, DI
		SHL BX, 2

        MOV AX, DI
        XOR DX, DX
		MUL CX
		
		MOV BP, AX
		ADD BP, SI
		SHL BP, 2

		MOV DX, DS:ARRAYS_OLD[BX + 2]
		MOV AX, DS:ARRAYS_OLD[BX]
		
		MOV DS:ARRAYS_NEW[BP + 2], DX
		MOV DS:ARRAYS_NEW[BP], AX
		
		INC DI
		CMP DI, COLS
		JB MAIN_INNER_LOOP
	
	INC SI
	CMP SI, ROWS
	JB MAIN_LOOP
	
	CALL CLEAR_SCREEN

	CALL CONVERT
	
	XOR BX, BX
	CALL PRINT
	
    MOV AX, 4C00H
    INT 21H

; ===== 打印缓冲区内容到屏幕 =====
PRINT:
    PUSH AX
    PUSH SI
    PUSH ES
    PUSH BX
    PUSH DI

    MOV AX, 0B800H       ; 显存段地址
    MOV ES, AX            ; ES指向显存
    
    MOV AH, 07H           ; 字符属性：浅灰底黑字
    LEA SI, DS:[BUFFER]   ; SI指向缓冲区起始位置
    
    XOR DI, DI            ; 数字计数器
PRINT_LOOP:
    MOV AL, DS:[SI]       ; 读取缓冲区中的字符
    CMP AL, 0H            ; 检查是否结束符（NULL）
    JE PRINT_OVER         ; 遇到结束符则结束打印 

    ; 检查字符类型
    CMP AL, ' '
    JE IS_SPACE
    
    JMP PRINT_CHAR
    
IS_SPACE:
    CMP DS:[SI + 1], ' '
    JE  PRINT_CHAR    
    INC DI
    
    ; 是空格字符
    CMP DI, NEWLINE_SIZES
    JNE PRINT_CHAR       
    
    XOR DI, DI           ; 重置数字计数器
    CALL NEWLINE         ; 执行换行操作
    JMP SKIP_SPACE       ; 跳过空格打印

PRINT_CHAR:
    ; 打印字符
    MOV ES:[BX], AX       ; 写入显存（字符+属性）
    ADD BX, 2             ; 移动到下一个显存位置
    
SKIP_SPACE:
    INC SI                ; 移动到缓冲区下一个字符
    JMP PRINT_LOOP        ; 继续打印

PRINT_OVER:
    POP DI
    POP BX
    POP ES
    POP SI
    POP AX
    RET

; ===== 换行功能 =====
NEWLINE:
    PUSH AX
    PUSH DX
    PUSH CX
    
    ; 计算下一行起始位置
    MOV AX, BX            ; 当前显存位置
    MOV CX, 160           ; 每行160字节（80字符×2）
    XOR DX, DX
    DIV CX                ; AX = 行号, DX = 列偏移
    
    ; 计算下一行起始位置
    INC AX                ; 下一行
    MUL CX                ; AX = 新行起始位置
    MOV BX, AX            ; 更新显存位置
    
    POP CX
    POP DX
    POP AX
    RET

; ===== 将数值数组转换为字符串 =====
CONVERT:
    PUSH AX
    PUSH CX
    PUSH DX
    PUSH SI
    PUSH DI

    LEA SI, ARRAYS_NEW   ; SI = 数组偏移
    LEA DI, BUFFER   ; DI = 缓冲区起始位置
    MOV BYTE PTR DS:[DI], 0 ; 缓冲区初始为NULL（安全措施）
    
	MOV CX, ARRAYS_SIZES
CONVERT_LOOP:
    MOV AX, DS:[SI]
    MOV DX, DS:[SI + 2]

    PUSH CX               ; 保存外部循环计数器
    
    ; ===== 内部循环（数值转字符串） =====
    CONVERT_INNER_LOOP:
        MOV CX, 10        ; 设置除数为10
        CALL DIVDW        ; 执行32位除法（DX:AX / 10）
        
        ADD CL, 30H       ; 余数转换为ASCII字符（0-9 → '0'-'9'）
        MOV DS:[DI], CL   ; 存储字符到缓冲区
        INC DI            ; 移动到缓冲区下一个位置
        
        ; 检查商是否为0
        CMP AX, 0H
        JNE CONVERT_INNER_LOOP
        CMP DX, 0H
        JNE CONVERT_INNER_LOOP
    
    MOV CX, SPACE
    ADD_SPACE:
        MOV BYTE PTR DS:[DI], ' ' ; 数字后添加空格分隔符
        INC DI                ; 移动到缓冲区下一个位置
    LOOP ADD_SPACE

    POP CX                ; 恢复外部循环计数器

    ADD SI, 4             ; 移动到数组下一个元素（4字节）
    LOOP CONVERT_LOOP      ; 继续转换下一个元素

    MOV BYTE PTR DS:[DI - 1], 0 ; 将最后一个空格设为结束符
    CALL REVERT           ; 反转字符串

    POP DI
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
    PUSH BX
    PUSH AX
    
    MOV AX, DX           ; 高16位移动到AX
    XOR DX, DX           ; 高位扩展为0
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
