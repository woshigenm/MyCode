assume cs:code

data segment
    Db 3 DUP(0)
data ends

; 检测点 9.1
code segment
start:
    mov ax,data
    mov ds,ax
    mov bx,0
    jmp word ptr [bx+1]
code ends

end start
