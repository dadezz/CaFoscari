/*

int pow2(int x) {
    return x*x;
}
int array[10] = {3,10,4,3,4,5,3,7,1,9}; 
void main() {
   int i = 0;
   int n = 0;
   do {
        n = pow2(array[i]);
        i++;
   } while(i<10);
}

*/
.text

    mov     w1,     #0
    mov     w2,     #0
entry_loop:
    adr     x3,     array
    ldr     w4,     [x3]
    b       pow2
    add     x3,     x3,     #4
    add     w1,     w1,     #1
    cmp     w1,     #10
    b.lt    entry_loop
pow2:
    mul     w2,     w4,     w4
    RET 
.data
array: 
    .word 3, 10, 4, 3, 4, 5, 3, 7, 1, 9