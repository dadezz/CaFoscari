    /*
    * Unione modalità
    * 
    * abbozzo più probabile per struttura programma finale, con gestione challenges
    * 
    * 
    * #include [librerie]
    * #include [file di funzioni] gestione_io e gestione 2 modalità: interattiva e IA come indicate qui sotto
    *
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
    * 
    * //////////////////////////////////////////////////////////////////////////////////
    * 
    * int chiedi_modalita(){
    *       int risposta;
    *       do {
    *           printf("vuoi giocare tu o testare IA? (1 per inter, 2 per IA");
    *           scanf("%d", &risposta);
    *       } while (risposta != 1 && risposta != 2);
    * }
    * 
    * int main (int argc, char* argv[]){
    * 
    *       struttura_lab_default = {###################
    *                                ###################
    *                                ###################}
    *       
    *       CONTROLLO ARGC E ARGV:
    *           if (numero di argomenti insensato){errore}
    *           if (contenuto di argomenti insensato) {errore}
    * 
    *       if (argv[1]==challenge){
    *           blcco_challenge(argv);
    *               questo blocco alla fine altro non sarà che una chiamata alla modalità IA 
    *               con questi dati: colonne e righe in input da argv e labirinto in se in input da tastiera (gestione come su test/test_ext)
    *           return 0;
    *       }
    *       else  risposta = chiedi_se_vuole_usare_labirinto_default();
    *       switch (risposta) {
    *           case sì: 
    *               if (chiedi_modalita == 1) MOD_INTERATTIVA (struttura_lab_default, colo_default, righe_default);
    *               else IA (struttura_lab_default, colo_default, righe_default);
    *               break;
    *           case 2: 
    *               ricevi_lab_in_input(); (gestione come su test/test_ext)
    *               if (chiedi_modalita == 1) MOD_INTERATTIVA (struttura_lab_default, colo_default, righe_default);
    *               else IA (struttura_lab_default, colo_default, righe_default);
    *       }
    *       return 0;      
    * }
    * */