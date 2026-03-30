ASSUME CS:CODESG   

CODESG SEGMENT                         
    
  DW 0123H, 0456H, 0789H, 0ABCH, 0DEFH, 0FEDH, 0CBAH, 0987H
  DW 0H, 0H, 0H, 0H, 0H, 0H, 0H, 0H, 0H, 0H   
  
START: MOV AX, CS
       MOV SS, AX
       MOV SP, 36

       MOV AX, 0H
       MOV DS, AX
       MOV BX, 0H  
       
       MOV CX, 8H
    S: PUSH DS:[BX]
       POP CS:[BX]
       ADD BX, 2H
       LOOP S

       MOV AX, 4C00H
       INT 21H
CODESG ENDS  

END START