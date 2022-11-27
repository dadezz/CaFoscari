    /*
    * Unione modalità
    * 
    * abbozzo struttura programma finale
    * 
    * 
    * #include [...]
    * #include [...]
    *
    * extern funzioni varie che servono nei blocchi logici
    * 
    * int IA (struttura lab, colo, righe){
    *       BLOCCO LOGICO ISTRUZIONI IA
    *       return 0;
    * }
    * 
    * int MOD_INTERATTIVA (struttra lab, colo, righe){
    *       BLOCCO LOGICO ISTRUZIONI INTER.
    *       return 0;
    * }
    * 
    * int chiedi_modalita(){
    *       int risposta;
    *       do {
    *           printf("vuoi giocare tu o testare IA? (1 per inter, 2 per IA");
    *           scanf("%d", &risposta);
    *       } while (risposta != 1 && risposta != 2);
    * }
    * 
    * int main (){
    * 
    *       struttura lab 1 = {###################
    *                          ###################
    *                          ###################}
    * 
    *       struttura lab 2 = {###################
    *                          ###################
    *                          ###################}
    * 
    *       struttura lab 3 = {###################
    *                          ###################
    *                          ###################}
    *       
    *       stampo i 3 lab (grafica carina plis)
    * 
    *       domanda: con quale labirinto vuoi giocare? [while controllo 1, 2, 3]
    *       
    *       switch (risposta) {
    *           case 1: 
    *               if (chiedi_modalita == 1) MOD_INTERATTIVA (struttura lab 1, colo1, righe1);
    *               else IA (struttura lab 1, colo1, righe1);
    *               break;
    *           case 2: 
    *               if (chiedi_modalita == 1) MOD_INTERATTIVA (struttura lab 2, colo2, righe2);
    *               else IA (struttura lab 2, colo2, righe2);
    *               break;
    *           case 3: 
    *               if (chiedi_modalita == 1) MOD_INTERATTIVA (struttura lab 3, colo3, righe3);
    *               else IA (struttura lab 3, colo3, righe3);
    *               break;
    *       }
    *       return 0;      
    * }
    * */