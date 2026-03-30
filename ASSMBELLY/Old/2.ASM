assume cs:codesg

codesg segment

  MOV AX, 0FFFFH
  MOV DS, AX
  
  MOV AX, 020H
  MOV ES, AX
  
  MOV CX, 010H
  MOV BX, 0H
F:MOV BYTE PTR ES:[BX], 0H
  INC BX
  LOOP F
  
  MOV AX, 020H
  MOV SS, AX
  MOV SP, 0EH
	
  MOV BX, 0DH
  MOV CX, 07H
S:MOV AH, DS:[BX]
  MOV AL, DS:[BX - 1]
  PUSH AX
  DEC BX
  DEC BX
  LOOP S
  
;  MOV CX, 07H
;L:POP AX
;  LOOP L
  
  MOV AX,4C00H
  INT 21H
   
codesg ends

end
