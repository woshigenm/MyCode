assume cs:codesg

codesg segment
	;5.5 FFFF:0 ~ FFFF:B 数据求和
START:
	MOV AX, 0FFFFH
	MOV DS, AX
	
	XOR BX, BX
	XOR DX, DX
	
    MOV CX, 6
  S:MOV AX, [BX]
	ADD DX, AX
	ADD BX, 2
	LOOP S
	
	mov ax,4c00h
	int 21h

codesg ends

end START