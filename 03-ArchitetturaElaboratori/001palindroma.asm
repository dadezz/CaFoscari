palindroma:
    adr     x1,     stringa
    ldrb    w2,     [x1]
    mov     x3,     x1
    cmp     w2,     #0
    b.eq    return_1
loop_1: 
    add     x3,     x3,     #1
    ldrb    w2,     [x3]
    cmp     w2,     #0
    b.ne    loop_1
    add     x3,     x3,     #1
loop_2:
    ldrb    w2,     [x1]
    ldrb    w4,     [x3]
    cmp     w2,     w4
    b.ne    return_0
    add     x1,     x1,     #1
    add     x3,     x3,     #-1
    cmp     x1,     x3
    b.hi    loop_2
    b       return_1
return_1:
    movz    x0,     #1
    ret 
return_0:
    movz    x0,     #0
    ret
