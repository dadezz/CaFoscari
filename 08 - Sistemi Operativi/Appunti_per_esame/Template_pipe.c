#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  int fd[2]; // i due descrittori
 
  pipe(fd); /* crea la pipe */
  
  if (fork() == 0) { // il processo figlio scrive
    char *phrase = "prova a inviare questo!";
 
    close(fd[0]);                         /* chiude in lettura */
    write(fd[1],phrase,strlen(phrase)+1); /* invia anche 0x00 */
    close(fd[1]);                         /* chiude in scrittura */
  
  } else {  // il processo genitore legge
    
    char message[100];
    memset(message,0,100);
    int bytesread;
 
    close(fd[1]);                         /* chiude in scrittura */
    bytesread = read(fd[0],message,99);   /* legge il messaggio */
    close(fd[0]);                         /* chiude in lettura */
  }
}