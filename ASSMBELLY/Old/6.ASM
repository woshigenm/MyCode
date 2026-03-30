assume cs:code

code segment
	
	MOV AX, CS
	MOV DS, AX
	MOV AX, 0020H
	MOV ES, AX
	MOV BX, 0
	MOV CX, 17H
	S:MOV AL, [BX]
	MOV ES:[BX], AL
	INC BX
	LOOP S
	
	MOV AX, 4C00H
    INT 21H

code ends

end