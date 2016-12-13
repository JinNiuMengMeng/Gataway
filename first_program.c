#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void kill_program(void){
	char buf[20] = {0};
	pid_t pid = getpid();
	strcat(buf, "kill -9 ");
	sprintf(buf+8, "%d", pid);
	buf[strlen(buf)] = '\0';
	system(buf);
}

int main(){
	sleep(1);
	system("./opt/second_program");
	kill_program();
	return 0;
}
