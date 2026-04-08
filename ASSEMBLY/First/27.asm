assume cs:code

data segment
    dd 12345678H
data ends

;
code segment
start:
    mov ax,data
    mov ds,ax
    mov bx,0
    mov word ptr [bx],offset start; mov [bx], bx
    mov [bx+2], code; mov [bx+2], cs
    jmp dword ptr ds:[0]
code ends

end start