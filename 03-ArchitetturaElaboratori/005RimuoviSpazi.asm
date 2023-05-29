/*
Si scriva una funzione Assembly ARM 64 che prenda in input una stringa e la
modifichi rimuovendo tutti gli spazi (codice ASCII 0x20). La funzione ritorna il
numero di spazi eliminati.
*/

/* RELATIVO CODICE C:

int elimina(char* a){
    char* dest = a;
    int spazi = 0;
    do{
        char c = *a;
        if (c == '/0') return spazi;
        if (c != ' '){
            *dest = c;
            dest++;
        }
        else {
            spazi++;
        }
        a++;
    } while (1);
}
*/

.global rimuovi

rimuovi:
    mov x1, x0
    mov x2, x0
    mov x3, #0
init_loop:
    ldrb w4, [x1]
    cmp w4, #0
    b.eq return_spazi
    cmp w4, #0x20
    b.ne branch_if
    b branch_else
continuazione:
    add x1, x1, #1
branch_else:
    add x3, x3, #1
    b continuazione
branch_if:
    strb w4, [x2]
    add x2, x2, #1
    b continuazione
return_spazi:
    mov x0, x3
    ret