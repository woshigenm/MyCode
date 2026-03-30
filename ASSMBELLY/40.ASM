ASSUME CS:CODE         ; 告诉汇编器CS寄存器指向代码段

; ===== 常量定义 =====
ARRAYS_SIZES EQU 10    ; 定义数组大小为10个元素

; ===== 数据段 =====
DATA SEGMENT
    ; 定义一个32位整数数组，包含10个元素
    ARRAYS DD 0FFFFFFFFH, 028C7D4FH, 0FBE21396H, 006DD89AH, 0C1F00421H, 0B5D780F2H, 0E24A6B13H, 05CC94A0EH, 074FE89C1H, 09B3A0D55H
    ; 定义一个128字节的缓冲区，用于存储转换后的字符串
    BUFFER DW 128 DUP(0)   ; 字符串缓冲区（128个零初始化）
DATA ENDS

; ===== 堆栈段 =====
STACK SEGMENT
    DB 128 DUP(0)           ; 128字节的堆栈空间（全部初始化为0）
STACK ENDS

; ===== 代码段 =====
CODE SEGMENT
START:
    MOV AX, DATA         ; 初始化数据段寄存器
    MOV DS, AX           ; DS指向数据段
    
    MOV AX, STACK        ; 初始化堆栈段寄存器
    MOV SS, AX           ; SS指向堆栈段
    MOV SP, 128          ; SP指向堆栈底部（128字节大小）
	
	CALL CLEAR_SCREEN
	
	CALL ISORT           ; 调用插入排序算法对数组排序
	
	CALL CONVERT         ; 将排序后的数组转换为字符串
	
	MOV BX, 0            ; 设置显存起始位置为0
	CALL PRINT           ; 打印转换后的字符串
	
	CALL SSORT           ; 调用插入排序算法对数组排序
	
	CALL CONVERT         ; 将排序后的数组转换为字符串
	
	MOV BX, 320            ; 设置显存起始位置为0
	CALL PRINT           ; 打印转换后的字符串
	
	CALL BSORT           ; 调用插入排序算法对数组排序
	
	CALL CONVERT         ; 将排序后的数组转换为字符串
	
	MOV BX, 640          ; 设置显存起始位置为0
	CALL PRINT           ; 打印转换后的字符串
	
	; ===== 程序结束 =====
	MOV AX, 4C00H        ; DOS功能调用：程序终止
	INT 21H              ; 执行DOS中断

; ===== 插入排序算法 =====
ISORT:
    PUSH AX
    PUSH BX      
    PUSH DX
    PUSH SI      
    
    MOV BX, 4    ; BX = 当前元素索引（字节偏移量），从第2个元素开始

; 外层循环：遍历数组中每个需要插入的元素（从索引1到末尾）
ISORT_MAIN_LOOP:
    MOV SI, BX            ; SI = 内层循环索引J（初始为I）
    SUB SI, 4             ; SI = J - 1（指向前一个元素）
    
    ; 加载当前元素值（32位）
    MOV DX, DS:[BX + 2]   ; DX = 当前元素的高16位（内存地址BX+2）
    MOV AX, DS:[BX]       ; AX = 当前元素的低16位（内存地址BX）

; 内层循环：在已排序部分查找插入位置
ISORT_INNER_LOOP:
    ; 比较当前元素和J元素的高16位
    CMP DS:[SI + 2], DX   ; 比较J元素高16位和当前元素高16位
    JA ISORT_MAIN_L       ; 如果J元素 > 当前元素（无符号高于），跳转到移动元素部分
    JB ISORT_MAIN_LOOP_END; 如果J元素 < 当前元素（无符号低于），找到插入位置，结束内层循环
    
    ; 高16位相等时，比较低16位
    CMP DS:[SI], AX       ; 比较J元素低16位和当前元素低16位
    JBE ISORT_MAIN_LOOP_END; 如果J元素 <= 当前元素（无符号低于或等于），找到插入位置，结束内层循环

; 移动元素部分：将J元素向后移动一位
ISORT_MAIN_L:
    ; 保存当前元素值
    PUSH DX
    PUSH AX
    
    ; 加载J元素值
    MOV DX, DS:[SI + 2]   ; DX = J元素高16位
    MOV AX, DS:[SI]       ; AX = J元素低16位
    
    ; 将J元素移动到J+1位置
    MOV DS:[SI + 6], DX   ; 存储J元素高16位到J+1位置（SI+6）
    MOV DS:[SI + 4], AX   ; 存储J元素低16位到J+1位置（SI+4）
    
    ; 恢复当前元素值
    POP AX
    POP DX
    
    SUB SI, 4             ; SI = J - 1（指向前一个元素）
    CMP SI, 0             ; 检查是否到达数组起始位置
    JGE ISORT_INNER_LOOP  ; 如果SI >= 0（J >= 0），继续内层循环

; 插入当前元素到正确位置
ISORT_MAIN_LOOP_END:
    ; 将当前元素插入到J+1位置
    MOV DS:[SI + 6], DX
    MOV DS:[SI + 4], AX
    
    ADD BX, 4             ; BX = BX + 4（指向下一个元素）
    
    ; 检查是否完成所有元素
    CMP BX, 4 * ARRAYS_SIZES ; 比较当前索引和数组结束位置（4 * 元素个数）
    JB ISORT_MAIN_LOOP    ; 如果BX < 4 * ARRAYS_SIZES，继续外层循环

    ; 恢复寄存器状态并返回
    POP SI
    POP DX
    POP BX
    POP AX
    RET
	
; ===== 选择排序算法 =====
SSORT:
	PUSH AX              ; 保存寄存器
	PUSH BX
	PUSH DI
	PUSH SI
	
	MOV BX, 0           ; BX = 当前最小元素索引（初始0）
SSORT_MAIN_LOOP:
	MOV SI, BX          ; SI = 当前最小元素位置
	
	MOV DI, SI          ; DI = 当前比较元素（从SI+4开始）
	ADD DI, 4H          ; DI = SI + 4（下一个元素）
	
	; ===== 内部循环（查找最小值） =====
	SSORT_MAIN_INNER_LOOP:
		MOV DX, DS:[SI + 2] ; 加载当前最小元素高16位
		MOV AX, DS:[SI]     ; 加载当前最小元素低16位
		
		; 比较当前最小元素和DI指向元素
		CMP DX, DS:[DI + 2] ; 比较高16位
		JB SSORT_UPDATE_MIN ; 若大于则更新最小元素位置
		JA SSORT_NOT_UPDATE ; 若小于则跳过
		
		; 高16位相等时比较低16位
		CMP AX, DS:[DI]     ; 比较低16位
		JA SSORT_NOT_UPDATE ; 若小于则跳过
	
	SSORT_UPDATE_MIN:
		MOV SI, DI          ; 更新最小元素位置
		
	SSORT_NOT_UPDATE:
		ADD DI, 4H          ; 移动到下一个元素（DI += 4）
		CMP DI, 4 * ARRAYS_SIZES ; 检查是否到达数组末尾
		JB SSORT_MAIN_INNER_LOOP ; 未结束则继续内部循环
	
	; ===== 交换元素 =====
	CMP SI, BX          ; 检查最小元素是否已正确位置
	JE SSORT_MAIN_LOOP_END ; 若在正确位置则跳过交换
	
	; 交换SI和BX位置的元素
	MOV DX, DS:[SI + 2] ; 加载新最小元素高16位
	MOV AX, DS:[SI]     ; 加载新最小元素低16位
	
	XCHG DS:[BX + 2], DX ; 交换高16位
	XCHG DS:[BX], AX     ; 交换低16位
	
	MOV DS:[SI + 2], DX ; 存储回SI位置高16位
	MOV DS:[SI], AX     ; 存储回SI位置低16位
	
SSORT_MAIN_LOOP_END:	
	ADD BX, 4H          ; 移动到下一个起始位置（BX += 4）
	CMP BX, 4 * (ARRAYS_SIZES - 1) ; 检查是否完成所有元素
	JB SSORT_MAIN_LOOP  ; 未完成则继续外部循环
	
	POP SI              ; 恢复寄存器
	POP DI
	POP BX
	POP AX
	RET                 ; 返回调用者

; ===== 冒泡排序算法 =====
BSORT:
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    PUSH SI
    
    MOV CX, ARRAYS_SIZES - 1  ; 外循环次数 = N-1
    
BSORT_OUTER_LOOP:
    MOV SI, 0                 ; 交换标志 = 0 (无交换)
    MOV BX, 0                 ; 内循环索引 = 0
    
BSORT_INNER_LOOP:
    ; 加载当前元素 [BX]
    MOV DX, [BX + 2]          ; 高16位
    MOV AX, [BX]              ; 低16位
    
    ; 比较当前元素和下一个元素 [BX] 和 [BX+4]
    CMP DX, [BX + 6]          ; 比较高16位
    JA  DO_SWAP               ; 当前 > 下一元素 → 交换
    JB  NO_SWAP               ; 当前 < 下一元素 → 跳过
    
    CMP AX, [BX + 4]          ; 比较低16位
    JBE NO_SWAP               ; 当前 <= 下一元素 → 跳过
    
DO_SWAP:
    XCHG [BX+6], DX
    XCHG [BX+4], AX
	
    MOV [BX+2], DX
    MOV [BX], AX
    
    MOV SI, 1                 ; 设置交换标志 = 1 (有交换)
    
NO_SWAP:
    ADD BX, 4                 ; 移动到下一元素
    CMP BX, 4 * (ARRAYS_SIZES - 1)  ; 检查边界
    JB  BSORT_INNER_LOOP      ; 继续内循环
    
    ; 检查交换标志
    TEST SI, SI               ; 检查是否有交换发生
    JZ  BSORT_END             ; 若无交换则提前结束
    
    DEC CX                    ; 外层循环计数器递减
    JNZ BSORT_OUTER_LOOP      ; 继续外层循环
    
BSORT_END:
    POP SI
    POP DX
    POP CX
    POP BX
    POP AX
    RET

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
END START ; 程序结束
