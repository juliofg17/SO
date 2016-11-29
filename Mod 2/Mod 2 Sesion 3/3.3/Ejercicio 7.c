#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>


int main(int argc, char *argv[]){
	
	pid_t pid;

	if( (pid=fork())<0) {
		perror("\nError en el fork");
	exit(-1);
	}


	else if(pid==0) { //proceso hijo ejecutando el programa
		if( argc == 2 ){
			if( (execl("/usr/bin/ldd","ldd",argv[1],NULL)<0)) 
				perror("\nError en el execl");
			
		}
		else 
			if( argv[argc-1] != "bg" ){
				if( (execv("/usr/bin/ldd", argv) < 0))
					perror("\nError en el execl");
				
 		        }
		
		else {
			argv[argc] = "&";
			argc++;
			if( (execv("/usr/bin/ldd", argv) < 0))
				perror("\nError en el execl");
			
		}
	}



return(0);
exit(-1);
}

