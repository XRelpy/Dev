    org 07c00h
    mov ax, cs
    mov ds, ax
    mov es, ax
    call DispStr     ;调用显示字符串
    jmp $                                       ; loop

DispStr:
    mov ax, BootMessage
    mov bp, ax      ; ES:BP = 串地址
    mov cx, 16      ; CX = 字符串长度
    mov ax, 01301h ; AH=13, AL = 01h
    mov bx, 000ch   ;页号为0 (BH = 0) 黑底红字(BL = 0CH, 高亮)
    mov dl, 0
    int 10h     ; 10h 号中断
    ret

  BootMessage:  db "Hello, OS world!"
  times 510-($-$$)  db 0    ;填充剩下的空间，使生成的二进制代码为512字节
  dw 0xaa55 ;结束标志
