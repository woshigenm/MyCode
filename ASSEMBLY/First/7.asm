assume cs:code

code segment
	
	DW 0123H,0456H,0789H,0ABCH,0DEFH,0FEDH,0CBAH,0987H

START:	
	MOV BX, 0
	MOV AX, 0
	
	MOV CX, 8
  S:ADD AX, CS:[BX]
	ADD BX, 2
	LOOP S
	
	MOV AX, 4C00H
    INT 21H

code ends

end START