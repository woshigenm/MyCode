assume cs:codesg

codesg segment
	;5.8 FFFF:0 ~ FFFF:B 数据复制到 0:200 ~ 0:02B
START:
	MOV AX, 0FFFFH
	MOV DS, AX
	
	MOV AX, 0H
	MOV ES, AX
	
	XOR BX, BX
	
	MOV CX, 6
  S:MOV DX, DS:[BX]
	MOV ES:[BX], DX
	ADD BX, 2
	LOOP S
	
	mov ax,4c00h
	int 21h

codesg ends

end START