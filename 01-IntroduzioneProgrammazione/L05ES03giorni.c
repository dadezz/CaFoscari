/*
Scrivere una funzione che dati 3 interi giorno, mese e anno, restituisca il
numero di giorni trascorsi dall’inizio dell’anno
*/
#include <stdio.h>

int giorni_trascorsi (int anno, int mese, int giorno){
    {//blocco 0: controllo che i numeri siano tutti positivi:
        if (mese<=0 || giorno<=0) return -1;
    }
    
    {//primo blocco: controllo che il numero di mesi sia sensato
        if (mese>12) return -1;
    }

    short bisestile = 0; //inizializzo a false
    {//secondo blocco: controllo anno bisestile
        if (anno%400==0 || (anno%4==0 && anno%100!=0)) bisestile =1;
    }

    short mese30 = 1; //inizializzo "il mese ha 30 giorni" a true.
    {//terzo blocco: controllo che il numero di giorni sia sensato
        if (mese!=2 && mese!=4 && mese!=9 && mese!=11) mese30 = 0;
        if (mese30==1 && giorno>30) return -1;
        if (mese30==0) {
            if ((mese==2 && bisestile==0 && giorno>28) || (mese==2 && bisestile==1 && giorno>29)) return -1;
            if (giorno>31) return -1;
        }
    }

    {//posso ora contare i giorni (sono sicuro che tutti i valori siano sensati)
        //inizio dai bisestili
        if (bisestile==1){
            switch (mese){
                case 1:
                    return (giorno-1); //il "-1" è perché il giorno in corso non è "trascorso"
                case 2:
                    return (31 + giorno - 1);
                case 3:
                    return (60 + giorno - 1);
                case 4:
                    return (91 + giorno - 1);
                case 5:
                    return (121 + giorno - 1);
                case 6:
                    return (152 + giorno - 1);
                case 7:
                    return (182 + giorno - 1);
                case 8:
                    return (213 + giorno - 1);
                case 9:
                    return (244 + giorno - 1);
                case 10:
                    return (274 + giorno - 1);
                case 11:
                    return (305 + giorno - 1);
                case 12:
                    return (335 + giorno - 1);
            }
        }
        else {
            switch (mese){
                case 1:
                    return (giorno-1);
                case 2:
                    return (31 + giorno - 1);
                case 3:
                    return (60 + giorno - 2);
                case 4:
                    return (91 + giorno - 2);
                case 5:
                    return (121 + giorno - 2);
                case 6:
                    return (152 + giorno - 2);
                case 7:
                    return (182 + giorno - 2);
                case 8:
                    return (213 + giorno - 2);
                case 9:
                    return (244 + giorno - 2);
                case 10:
                    return (274 + giorno - 2);
                case 11:
                    return (305 + giorno - 2);
                case 12:
                    return (335 + giorno - 2);
            }
        }
    }
}

int main (){
    int output = giorni_trascorsi(2022, 12, 31);
    if (output == -1){
        printf("ci dev'essere stato un errore con l'input\n");
    }
    else {
        printf("il numero di giorni già trascorsi è: %d\n", output);
        printf("questo è il giorno numero: %d\n", output+1);
    }
    return 0;
}