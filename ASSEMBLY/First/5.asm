assume cs:codesg

codesg segment
	;实验四,(2) 0:200 ~ 0:23F 传递 0 ~ 63
	MOV AX, 0
	MOV DS, AX
	
	MOV BX, 200H
	
	MOV CX, 040H
  S:MOV DS:[BX], BL
	INC BX
	LOOP S
	
	MOV AX, 4C00H
    INT 21H

codesg ends

end