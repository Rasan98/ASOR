#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main (int argc, char* argv[]){
	
	int p_h[2];
	int h_p[2];
	
	if(pipe(p_h) == -1){
		perror("pipe_p_h");
		return -1;
	}
	
	if(pipe(h_p) == -1){
		perror("pipe_h_p");
		return -1;
	}
	
	int pid; 
	if((pid = fork()) == -1){
		perror("fork");
		return -1;
	}
	
	if (pid == 0){
	//hijo	
		if(close(p_h[1]) == -1){
			perror("close_hijo");
			return -1;
		}
	
		if(close(h_p[0]) == -1){
			perror("close2_hijo");
			return -1;
		}
		
		int i = 0;
		int leido;
		for(;i < 10; i++){
			char buf[100];
			leido = read(p_h[0], buf, 100);
			//buf[leido] = '\0';	
			printf("Hijo dice: %s\n", buf);
			sleep(1);
			if(i != 9)
				write(h_p[1], "l", 1);
		}	
		write(h_p[1], "q", 1);
		return 1;
	}
	else{
	//padre	
		if(close(p_h[0]) == -1){
			perror("close_padre");
			return -1;
		}
	
		if(close(h_p[1]) == -1){
			perror("close2_padre");
			return -1;
		}
		
		
		char ans;
		do{
			char buf[100];
			int leido = read(0, buf, 100);
			write(p_h[1], buf, leido);
			read(h_p[0], &ans, 1);
		}while(ans != 'q');
		return 1;
	}
}
