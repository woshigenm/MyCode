assume cs:codesg

codesg segment
	;实验四(3) 指令复制到内存 0:200 处
	
	MOV AX, CS; 2
	MOV DS, AX; 2
	
	MOV AX, 0020H; 3
	MOV ES, AX; 2
	
	MOV BX, 0; 3
	MOV CX, 17H; 3
  S:MOV AL, [BX]; 2
	MOV ES:[BX], AL; 2
	INC BX; 1
	LOOP S; 1
	
	MOV AX, 4C00H
    INT 21H

codesg ends

end