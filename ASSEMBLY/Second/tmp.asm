ASSUME CS:CODE

CODE SEGMENT
START:
    MOV AX, 30
    CALL SHOWSIN

    MOV AX, 4C00H
    INT 21H

SHOWSIN:
     JMP SHORT SHOW
ERRORS DB 'INPUT ERROR!','$'
    TABLE DW AG0,AG30,AG60,AG90,AG120,AG150,AG180	;字符串偏移地址表
    AG0      DB '0',0			;SIN(0)对应的字符串“0”
    AG30     DB '0.5',0			;SIN(0)对应的字符串“0.5”
    AG60     DB '0.866',0		;SIN(0)对应的字符串“0.866”
    AG90     DB '1',0			;SIN(0)对应的字符串“1”
    AG120    DB '0.866',0		;SIN(0)对应的字符串“0.866”
    AG150    DB '0.5',0			;SIN(0)对应的字符串“0.5”
    AG180    DB '0',0			;SIN(0)对应的字符串“0”
LEGALVALUE DW 0,30,60,90,120,150,180

SHOW:PUSH BX
     PUSH ES
     PUSH SI
     PUSH CX
     
     CMP AX, 180
     JA PRINT_ERROR
     CMP AX, 0
     JB PRINT_ERROR
     
     MOV CX, 7
     XOR SI, SI
     S:    
         CMP AX, CS:[LEGALVALUE + SI]
         JE CONTINUE
         ADD SI, 2 
     LOOP S
     
     JMP SHORT PRINT_ERROR

CONTI:        
     MOV BX,0B800H
     MOV ES,BX

     MOV BX, SI
     MOV BX,CS:TABLE[BX]

;以下IN(X)对应的字符串
     MOV SI,160*12+40*2
SHOWS
	MOV AH,CS:[BX]
     CMP AH,0
     JE SHOWRET
     MOV ES:[SI],AH
     INC BX
     ADD SI,2
     JMP SHOWS
PRINTROR:  
     MOV AX, CS
     MOV DS, AX

     MOV DX, OFFSET ERRORS 
     MOV AH, 9
     INT 21H        
SHOWR
     POP CX
     POP SI
     POP ES
     POP BX
     RET

CODE ENDS
END START