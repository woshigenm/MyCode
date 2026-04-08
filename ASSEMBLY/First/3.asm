assume cs:codesg

codesg segment

	MOV AX, 0FFFFH
	MOV DS, AX
	
	MOV AX, 020H
	MOV ES, AX
	
	MOV CX, 0CH ; 12个存储单元
	MOV BX, 0H ; 每个存储单元的偏移量
  F:MOV BYTE PTR ES:[BX], 0H ; 将存储单元置为 0
    INC BX
	LOOP F
	
	MOV CX, 0CH ; 12个存储单元
	MOV BX, 0H ; 每个存储单元的偏移量
	
  S:MOV DL, DS:[BX]
	MOV ES:[BX], DL
	INC BX
	LOOP S
	
	MOV AX, 4C00H
    INT 21H

codesg ends
end