assume cs:codesg

codesg segment

   MOV AX, 0FFFFH
   MOV DS, AX
   MOV AX, 020H
   MOV ES, AX
   
   MOV BX, 0
   MOV CX, 0CH
 S:MOV AL, DS:[BX]
   MOV ES:[BX], AL
   INC BX
   LOOP S
   
   MOV AX,4C00H
   INT 21H
   
codesg ends

end
