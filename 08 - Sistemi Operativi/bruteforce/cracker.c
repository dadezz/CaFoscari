#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
	int status;
	for (int i = 0; i<50000; i++){
		pid_t pid = fork();
		if (pid == 0){
			char pin_str[128];
			snprintf(pin_str, 128, "%05d", i);
			//printf("provando pin %d", i);
			printf(pin_str);
			execlp("./bruteforce", "./bruteforce", pin_str, NULL);
		}
		else if (pid<0) {
			printf("fork non riuscita\n");
			break;
		}
		int boolean = 0;
		while((pid=wait(&status)) >= 0){
			if (WIFEXITED(status))
				if (WEXITSTATUS(status) == 0){
					printf("pin corretto: %d \n", i);
					boolean = 1;
				}
			else if (WIFSIGNALED(status))
				printf("ANOMALO: status= %d \n", WTERMSIG(status));
		}
		if (boolean) exit(EXIT_SUCCESS);
	}
return 0;
}
