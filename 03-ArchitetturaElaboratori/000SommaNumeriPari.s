/*
for(int i=0; i<n; ++i){
    if(i%2 == 0) r++;
}
*/

.text

    adr     x0,     n
    ldr     w0,     [x0]
    mov     w1,     #0
    mov     w2,     #0
    cmp     w2,     w0
    b.ge    exit_for
init_for:
    ands    w3,     w2,     #1
    b.ne    skip_1
    add     w1,     w1,     w2
skip_1:
    cmp     w2,     w0
    b.lt    init_for
exit_for:
    adr     x0,     r
    str     w1,     x0

.data

    .global n

n:  .word 0

    .global r
    
r:  .word 0
