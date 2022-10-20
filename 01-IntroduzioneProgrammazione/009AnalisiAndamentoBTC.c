/*
Analisi andamento bitcoin
Scrivere una funzione che implementi una strategia di acquisto e vendita.
    ○ quanto comprare, quando vendere?
Possibili strategie:
    ○ strategia I: se la media mobile è crescente c’è un trend di crescita: compra! (viceversa vendi)
    ○ strategia II: se la media mobile a breve termine supera la media mobile a lungo termine,
        significa che c’è un trend in crescita: compra! (viceversa vendi)
Definizione: la media mobile a w giorni di una data sequenza X è una nuova
sequenza che al giorno i assume valore pari alla media dei valori della
sequenza X nella finestra di w giorni che termina nel giorno i incluso.*/


#include<stdio.h>

//per prima cosa, mi faccio una funzione che, dati finestra w (periodo) e giorno, mi ritorni la media mobile 
float media_mobile (float *x, int x_size, int periodo, int giorno){
    //il bisogno dei vari "periodo-1" è dovuto al fatto che l'array inizia da 0 e non da 1.
    //se il periodo è 3 giorni, il giorno avrà indice 2

    if (giorno<periodo-1 || periodo>=x_size || giorno>=x_size){
        printf("valore senza senso\n");
        return -1; //se ci fosse stato input da utente, nel main ci sarebbe stato un while di controllo input...
    }
    else{
        int i = (giorno-(periodo-1)); //inizio a calcolare la media dal giorno (giorno che cerco - periodo precedente).
        float media = x[i]; // il primo valore che ha la media è quello del primo giorno, a cui verranno sommati quelli successivi
        while (i<giorno){ //nel ciclo faccio questo: alzo di uno l'indice del giorno e sommo il prezzo a quelli precedenti
            i += 1;
            media += x[i];
        }
        media = media/(periodo); //media = somma di tutti i prezzi / periodo preso in considerazione
        return media;
    }
}

//fatta la media mobile, posso implementare la strategia 1.
//stampo la stringa "compra" o "vendi" a seconda della crescita o decrescita della media mobile
int strategia_1 (float *x, int x_size, int periodo, int giorno){
    if (giorno-1 < periodo-1) {
        //printf("STRATEGIA 1: non si può calcolare la media, non posso dirti nulla\n");
        return 0;
    }
    float media_giorno_scorso = media_mobile (x, x_size, periodo, giorno-1);
    float media_oggi = media_mobile (x, x_size, periodo, giorno);
    if (media_giorno_scorso == -1 || media_oggi == -1) return 0; //controllo che non mi dia errore il calcolo della media mobile
    else {
        if (media_giorno_scorso < media_oggi) return 1;
        else if (media_giorno_scorso == media_oggi) return 3;
        else return 2;
    }
}

//implemento strategia 2. controllo quindi la differenza tra le due medie. se si sono incrociate,
//la differenza in un giorno sarà di segno discorde dalla differenza nel giorno dopo.
int strategia_2 (float *x, int x_size, int periodo_breve, int periodo_lungo, int giorno){
    if (giorno-1 < periodo_lungo-1) {
        //printf("STRATEGIA 2: è il primo giorno in cui si può calcolare la media a lungo periodo, non posso dirti nulla\n");
        return 0;
    }
    float media_breve_giorno_scorso = media_mobile (x, x_size, periodo_breve, giorno-1);
    float media_lunga_giorno_scorso = media_mobile (x, x_size, periodo_lungo, giorno-1);
    float media_breve_oggi = media_mobile (x, x_size, periodo_breve, giorno);
    float media_lunga_oggi = media_mobile (x, x_size, periodo_lungo, giorno);

    if (media_breve_giorno_scorso == -1 || media_breve_oggi == -1) return 0; //controllo che non mi dia errore il calcolo della media mobile
    else {
        if((media_lunga_giorno_scorso - media_breve_giorno_scorso >= 0) && (media_lunga_oggi - media_breve_oggi < 0))
            return 1;
        else if ((media_lunga_giorno_scorso - media_breve_giorno_scorso <= 0) && (media_lunga_oggi - media_breve_oggi > 0))
            return 2;
        else return 3;
    }
}




float backtest_strategia_1 (float dollari_partenza, float *x, int x_size, int periodo){
    //controllo backtest
    float wall_fiat = dollari_partenza; //dollari di partenza
    float wall_btc = 0.0f; //btc di partenza
    _Bool hobtc = 0; //possiedo btc?

    for (int i=0; i<x_size; i++){
        int cosa_faccio = strategia_1 (x, x_size, periodo, i);
        if (cosa_faccio == 1 && hobtc==0){  //return 1 se compra
            wall_btc = wall_fiat/x[i];
            //printf("ho comprato il giorno %d, partendo da %f dollari, acquistato %f bitcoin\n", i, wall_fiat, wall_btc);
            wall_fiat = 0;
            hobtc = 1;
        }
        else if(cosa_faccio == 2 && hobtc){
            wall_fiat = wall_btc*x[i];
            //printf("ho venduto il giorno %d, partendo da %f btc, riottenuto %f dollari\n", i, wall_btc, wall_fiat);
            wall_btc = 0;
            hobtc = 0;
        }
    }
    /* QUESTO ERA NEL CASO DI FUNZIONE VOID (CHE IN STO PROGRAMMA PREFERISCO), CON STAMPA DEI RISULTATI.
    NON MI PERMETTE PERÒ DI FARE AGEVOLMENTE I CONTROLLI CON TUTTI I POSSIBILI VALORI
    printf("al momento possiedo %f btc\n", wall_btc);
    printf("al momento possiedo %f dollari\n", wall_fiat);
    if (hobtc){
        printf("il controvalore dei miei btc in dollari è: %f\n", wall_btc*x[365]);
    }
    */
    if (hobtc) return wall_btc*x[365];
    else return wall_fiat;
}

float backtest_strategia_2 (float dollari_partenza, float *x, int x_size, int periodo_breve, int periodo_lungo){
    //controllo backtest
    float wall_fiat = dollari_partenza; //dollari di partenza
    float wall_btc = 0.0f; //btc di partenza
    _Bool hobtc = 0; //possiedo btc?

    for (int i=0; i<x_size; i++){
        int cosa_faccio = strategia_2 (x, x_size, periodo_breve, periodo_lungo, i);
        if (cosa_faccio == 1 && hobtc==0){  //return 1 se compra
            wall_btc = wall_fiat/x[i];
            //printf("ho comprato il giorno %d, partendo da %f dollari, acquistato %f bitcoin\n", i, wall_fiat, wall_btc);
            wall_fiat = 0;
            hobtc = 1;
        }
        else if(cosa_faccio == 2 && hobtc){
            wall_fiat = wall_btc*x[i];
            //printf("ho venduto il giorno %d, partendo da %f btc, riottenuto %f dollari\n", i, wall_btc, wall_fiat);
            wall_btc = 0;
            hobtc = 0;
        }
    }
    /* QUESTO ERA NEL CASO DI FUNZIONE VOID (CHE IN STO PROGRAMMA PREFERISCO), CON STAMPA DEI RISULTATI.
    NON MI PERMETTE PERÒ DI FARE AGEVOLMENTE I CONTROLLI CON TUTTI I POSSIBILI VALORI
    printf("al momento possiedo %f btc\n", wall_btc);
    printf("al momento possiedo %f dollari\n", wall_fiat);
    if (hobtc){
        printf("il controvalore dei miei btc in dollari è: %f\n", wall_btc*x[365]);
    }
    */
    if (hobtc) return wall_btc*x[365];
    else return wall_fiat;
}




//*****************************************************************************************************************************************************************
//                                                                      MAIN                                                                                      //
//****************************************************************************************************************************************************************//



int main (){
   
    //dati di prezzo giornaliero di un anno (366 giorni)
    float btc[] = {10923.63, 10679.14, 10621.66, 10804.00, 10684.43, 10565.49, 10585.16, 10623.33, 10787.62, 10848.83, 10721.33, 10774.43, 10754.44, 10702.29,
    10745.55, 10225.86, 10538.46, 10462.26, 10938.27, 11094.35, 10944.59, 10948.99, 10974.90, 10796.95, 10680.84, 10323.76, 10442.17, 10400.91,
    10363.14, 10242.35, 10131.52, 10369.56, 10280.35, 10169.57, 10511.81, 10245.30, 11414.03, 11970.48, 11680.82, 11711.51, 11506.87, 11542.50,
    11323.40, 11488.36, 11366.14, 11774.60, 11664.85, 11681.83, 11592.49, 11878.37, 11758.28, 11991.23, 12254.40, 11892.80, 11865.70, 11768.87,
    11784.14, 11584.93, 11410.53, 11878.11, 11675.74, 11754.05, 11601.47, 11779.77, 11747.02, 11205.89, 11246.35, 11053.61, 11759.59, 11323.47,
    11111.21, 11100.47, 10912.82, 10990.87, 9905.17, 9677.11, 9536.89, 9581.07, 9525.36, 9374.89, 9164.23, 9185.82, 9159.04, 9151.39, 9132.23, 9192.84,
    9243.21, 9243.61, 9276.50, 9240.35, 9278.81, 9277.97, 9428.33, 9252.28, 9375.47, 9073.94, 9132.49, 9087.30, 9123.41, 9228.33, 9137.99, 9190.85,
    9143.58, 9045.39, 9162.92, 9264.81, 9313.61, 9629.66, 9648.72, 9303.63, 9332.34, 9288.02, 9411.84, 9480.26, 9538.02, 9450.70, 9386.79, 9475.28,
    9480.84, 9321.78, 9870.09, 9795.70, 9771.49, 9758.85, 9653.68, 9665.53, 9800.64, 9656.72, 9529.80, 10167.27, 9461.06, 9700.41, 9439.12, 9525.75,
    9181.02, 8835.05, 8906.93, 8790.37, 9209.29, 9182.58, 9081.76, 9522.98, 9729.04, 9726.57, 9670.74, 9377.01, 9328.20, 9733.72, 9269.99, 8804.48,
    8601.80, 8756.43, 9593.90, 9842.67, 9951.52, 9268.76, 9003.07, 8912.65, 8897.47, 8988.60, 8864.77, 8658.55, 8801.04, 7807.06, 7795.60, 7679.87,
    7569.94, 7550.90, 7429.72, 7117.21, 6880.32, 6881.96, 7189.42, 7257.66, 7096.18, 7116.80, 6642.11, 6842.43, 6845.04, 6971.09, 6859.08, 6865.49,
    7302.09, 7334.10, 7176.41, 7271.78, 6791.13, 6867.53, 6733.39, 6793.62, 6606.78, 6438.64, 6429.84, 5922.04, 6242.19, 6469.80, 6716.44, 6681.06,
    6734.80, 6416.31, 5830.25, 6185.07, 6198.78, 6191.19, 5238.44, 5225.63, 5014.48, 5392.31, 5200.37, 5563.71, 4970.79, 7911.43, 7909.73, 7923.64,
    8108.12, 8909.95, 9122.55, 9078.76, 8755.25, 8787.79, 8869.67, 8562.45, 8599.51, 8672.46, 8784.49, 8820.52, 9341.71, 9650.17, 9924.52, 9663.18,
    9686.44, 9608.48, 9633.39, 10142.00, 9690.14, 9934.43, 9889.42, 10312.12, 10214.38, 10326.05, 10208.24, 9856.61, 10116.67, 9865.12, 9795.94,
    9729.80, 9613.42, 9180.96, 9293.52, 9344.37, 9392.88, 9350.53, 9508.99, 9316.63, 9358.59, 8909.82, 8596.83, 8367.85, 8445.43, 8406.52, 8680.88,
    8745.89, 8657.64, 8706.25, 8942.81, 8929.04, 8723.79, 8807.01, 8827.76, 8144.19, 8192.49, 8037.54, 8166.55, 7879.07, 8079.86, 8163.69, 7769.22,
    7411.32, 7410.66, 7344.88, 6985.47, 7200.17, 7193.60, 7293.00, 7422.65, 7317.99, 7290.09, 7238.97, 7275.16, 7322.53, 7355.63, 7511.59, 7191.16,
    7218.82, 7202.84, 7276.80, 6640.52, 6932.48, 7152.30, 7124.67, 7269.68, 7243.13, 7217.43, 7278.12, 7400.90, 7564.35, 7556.24, 7547.00, 7448.31,
    7252.03, 7320.15, 7321.99, 7424.29, 7569.63, 7761.24, 7463.11, 7531.66, 7218.37, 7146.13, 7047.92, 7397.80, 7296.58, 7642.75, 8027.27, 8206.15,
    8309.29, 8577.98, 8550.76, 8491.99, 8708.10, 8808.26, 8815.66, 8757.79, 9055.53, 8813.58, 8804.88, 9267.56, 9360.88, 9342.53, 9412.61, 9235.35,
    9324.72, 9261.10, 9199.58, 9205.73, 9427.69, 9256.15, 9551.71, 9244.97, 8660.70, 7493.49, 7514.67, 8078.20, 8243.72, 8222.08, 7988.56, 7973.21,
    8103.91, 8047.53, 8205.37, 8374.69, 8321.01, 8336.56, 8321.76, 8586.47, 8595.74};

    int x_size = 366;

    //vedo cosa avrei dovuto fare il giorno 12 agosto (giorno numero 224). usando la media a 3gg nella prima strategia e la media 3/7 gg nella seconda
    /*printf("cosa dovevo fare il 12 agosto?\n");
    strategia_1(btc, x_size, 3, 224);
    strategia_2(btc, x_size, 3,7, 224);
    printf("\n");
    */

    float dollari_partenza = 10000.0f;

    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("  STRATEGIA 1: quando la media mobile inizia a crescere, compra, quando inizia a scendere, vendi\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    float max_1 = 0;
    int periodo_ideale = 0;
    for (int i = 2; i < 360; i++){
        float prova = backtest_strategia_1(dollari_partenza, btc, 366, i);
        if (prova > max_1){
            periodo_ideale = i;
            max_1 = prova;
        }
    }
    printf("**********************************\n");
    printf("STRATEGIA 1: usando media mobile a %d periodi\n ", periodo_ideale);
    printf("possiedo (o ho come controvalore) %f dollari\n", max_1);
    
    
    
    
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("     STRATEGIA 2: compra o vendi a seconda di come (e se) la media breve inrocia quella lunga  \n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    float max_2 = 0;
    int periodo_breve_ideale = 0;
    int periodo_lungo_ideale = 0;
    for (int i_l = 2; i_l<300; i_l++){
        for (int i_b = 2; i_b<i_l; i_b++){
            float prova = backtest_strategia_2(dollari_partenza, btc, 366, i_b, i_l);
            if (prova > max_2){
                periodo_breve_ideale = i_b;
                periodo_lungo_ideale = i_l;
                max_2 = prova;
            }
        }
    }
    printf("STRATEGIA 2: usando media mobile lunga a %d periodi e la media mobile breve a %d periodi\n", periodo_lungo_ideale, periodo_breve_ideale);
    printf("possiedo (o ho come controvalore) %f dollari\n", max_2);
    printf("**********************************\n");
    
    
    return 0;
}