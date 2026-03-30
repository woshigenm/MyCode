assume cs:code

code segment
start:
    mov ax,2000H
    mov ds,ax
    xor bx,bx 
   
  s:
    mov cl,[bx]
    mov ch,0
    inc cx          ;
    inc bx
    LOOP  s
ok:
   DEC BX
    mov dx,bx
    mov ax,4c00h
    int 21h
   
code ends

end start
