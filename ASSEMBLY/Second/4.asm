assume code:cs

code segment
   
   MOV AX, 0020H
   MOV DS, AX
   
   MOV BX, 0H
   
   MOV CX, 64
S:       
   MOV DS:[BX], BL
   INC BX
   LOOP S
   
   MOV AX, 04C00H
   INT 21
    
code ends

end