/*
Si trasformi il seguente frammento di codice C in uno equivalente Assembly
ARM A64.
r = 1;
for( long i=0; i<n; ++i )
{
if( i%4 == 0)
r = r * 2;
}
Si assuma che le variabili r e n siano definite nel segmento .data in questo modo:
.data
.p2align 2
.global n
n: .dword 0
.global r
r: .dword 0
Nota: Non è permesso usare l’istruzione MUL.
*/
.text

    adr     x1,     r
    ldr     x2,     [x1]
    mov     x2,     #1
    adr     x3,     n
    ldr     x4,     [x3]
    mov     x5,     #0
    cmp     x5,     x4
    b.ge    exit_for

init_for:

    ands    x6,     x5,     #3
    b.ne    skip_1
    lsl     x2,     x2,     #2

skip_1:

    add     x5,     x5,     #1
    cmp     x5,     x4
    b.lt    init_for

exit_for:

    str     x2,     [x1]

.data
.p2align 2
    .global n
n: .dword 0
    .global r
r: .dword 0