/*
 * Corso di Sistemi Operativi 2021
 * Terza esercitazione: monitor
 *
 * Author: Riccardo Focardi
 *
 * Compilare con: javac Piazza.java
 */

 import java.util.Random;
 import java.util.HashMap;
 import java.util.List;
 import java.util.Arrays;
 import java.util.ArrayList;
 
 public class Piazza {
     final static int  N_THREAD=40;
     final static int SLEEPBASE=100;
     final static int N_ITER=20;
     final static Person[] person = new Person[N_THREAD];
     final static String contrade[] =  new String[] {"Chiocciola","Aquila","Civetta","Bruco"};
     private static int flag = 0;
     static Random rand = new Random(67);
     static private HashMap<String,Integer> n_persone = new HashMap<String,Integer>();
     static private HashMap<String,Integer> max_persone = new HashMap<String,Integer>();
     static private HashMap<String,List<String>> conflicts = new HashMap<String,List<String>>();
     static private HashMap<String,List<String>> permitted = new HashMap<String,List<String>>();
     static private List<String> checked = new ArrayList<String>();
 
     public static void main(String args[]) throws InterruptedException {
         int i,j,k;
 
         Monitor m = new Monitor();
 
         for (String kk : contrade) {
             permitted.put(kk,new ArrayList<String>());
         }
         conflicts.put("Chiocciola",Arrays.asList("Aquila", "Civetta", "Bruco"));
         conflicts.put("Aquila",Arrays.asList("Chiocciola", "Bruco"));
         conflicts.put("Civetta",Arrays.asList("Chiocciola"));
         conflicts.put("Bruco",Arrays.asList("Chiocciola", "Aquila"));
 
         for (String kk : contrade) {
             for (String p : contrade) {
                 if (p != kk && !conflicts.get(kk).contains(p)) {
                     permitted.get(kk).add(p);
                 } 
             }
         }
         // System.out.println(permitted);
 
         for(j=0;j<N_ITER;j++) {
             for (String kk : contrade) {
                 max_persone.put(kk,0);
                 n_persone.put(kk,0);
             }
             checked = new ArrayList<String>();
 
             for (i=0;i<N_THREAD;i++) {
                 k=rand.nextInt(4);
                 person[i] = new Person(j,m,k);
                 max_persone.put(contrade[k],max_persone.get(contrade[k])+1);
                 person[i].start();
             }
             // System.out.println(max_persone);
 
             for (String kk : contrade) {
                 if (max_persone.get(kk)==0) {
                     System.out.println(String.format("[ERRORE] Nessuna persona %s!",kk));
                     System.exit(1);
                 }
             }
 
             for (i=0;i<N_THREAD;i++) {
                 person[i].join();
             }
         }
         System.out.println(String.format("Terminato, flag=%06x",flag));
     }
 
     static class Person extends Thread {
         String contrada;
         Monitor m;
         int j;
 
         Person(int j,Monitor m, int k) {
             this.contrada = contrade[k];
             this.m = m;
             this.j = j;
             flag = (flag + (k*(rand.nextInt(16777216))))%16777216;
         }
 
         public void run() {
             try {
                 go();
             } catch (InterruptedException e) {
                 System.out.println(String.format("Persona %s interrotta!",contrada));
             }
         }
 
         public void go() throws InterruptedException {
             // System.out.println(String.format("Saluti dal thread di tipo %s", this.contrada));
             // m.test1();
 
 
             synchronized(m) {
                 m.entra(contrada);
                 System.out.println(String.format("[%s] entra in piazza", this.contrada));
 
                 n_persone.put(contrada,n_persone.get(contrada)+1);
 
                 for (String k : conflicts.keySet()) {
                     if (n_persone.get(k)>0) {
                         for (String c : conflicts.get(k)) {
                             if (n_persone.get(c)>0) {
                                 System.out.println(String.format("[ERRORE] %s assieme a %s",k,c));
                                 System.out.println(String.format("Stato: %s",n_persone));
                                 System.out.println(String.format("Iterazione: %d",j));
 
                                 System.exit(1);
                             }
                         }
                     }
                 }
             }
 
             sleep(SLEEPBASE);
 
             synchronized(m) {
                 m.esce(contrada);
                 if (!permitted.get(contrada).isEmpty() 
                     && !checked.contains(contrada) 
                     && n_persone.get(contrada) == max_persone.get(contrada)) 
                 {
                     boolean ok=false;
                     for (String k : permitted.get(contrada)) {
                         if (n_persone.get(k)==max_persone.get(k)) {
                             ok=true;
                             checked.add(k);
                         }
                     }
                     if (!ok) {
                         ok=true;
                         for (String k : permitted.get(contrada)) {
                             if (!checked.contains(k)) {
                                 ok=false;
                                 break;
                             }
                         }
                     }
                     if (!ok) {
                         System.out.println(String.format("[ERRORE] uno di %s non è entrato insieme a %s!",permitted.get(contrada), contrada));
                         System.out.println(String.format("Stato: %s",n_persone));
                         System.out.println(String.format("Iterazione: %d",j));
 
                         System.exit(1);
                     }
                     checked.add(contrada);
                 }
                 n_persone.put(contrada,n_persone.get(contrada)-1);
             }
 
             System.out.println(String.format("[%s] esce dalla piazza", this.contrada));
         }
     }
 }

 /**
  * autore Davide Zambon,
  * esercitazione sui monitor
  * intuitivamente: c'è una variabile che conta quante persone ci sono per ogni contrada, in modo che le persone appartenenti alle altre
  * contrade possano entrare in piazza solo quando non ci sono più persone delle contrade nemiche. 
  * il contatore specifico di ogni contrada viene incrementato quando la persona entra in piazza e decrementato quando esce. 
  * prima di entrare, ognuno aspetta finché la situazione in piazza non è ok con le condizioni, poi entra, fa il suo e quando esce 
  * avvisa tutti gli altri, che possano ricontrollare se possono entrare
  */

 class Monitor {
    // gli int rappresentano la domanda "Quante persone sono presenti in piazza?" . potevo fare un array ma mi è venuto più comodo
    // separare le variabili tra loro in modo da avere chiaro riferimento ai nomi, invece di ricordarmi gli indici
    int chiocciola, bruco, aquila, civetta;

    Monitor() {
        chiocciola = bruco = aquila = civetta = 0;
    }

    synchronized void entra(String contrada) throws InterruptedException {
        switch(contrada) {
            // ogni contrada ha le sue condizioni
            case "Chiocciola":
                while(bruco>0 || aquila>0 || civetta>0) 
                    wait();
                chiocciola++;
                break;
            case "Bruco":
                while(chiocciola>0 || aquila>0) 
                    wait();
                bruco++;
                break;
            case "Aquila":
                while(chiocciola>0 || bruco>0) 
                    wait();
                aquila++;
                break;
            case "Civetta":
                while(chiocciola>0) 
                    wait();
                civetta++;
                break;
            default:
            // controllo non ci siano errori di scrittura
                System.out.println("caso sbagliato");
          }
          
    }

    synchronized void esce(String contrada) {
        // quando la contrada esce decrementa la sua variabile e notifica gli altri
        switch (contrada) {
            case "Chiocciola":
                chiocciola--;
                notifyAll();
                break;
            case "Bruco":
                bruco--;
                notifyAll();
                break;
            case "Aquila":
                aquila--;
                notifyAll();
                break;
            case "Civetta":
                civetta--;
                notifyAll();
                break;
            default:
            // controllo non ci siano errori di scrittura

                System.out.println("contrada sbagliata");
        }
    }
}