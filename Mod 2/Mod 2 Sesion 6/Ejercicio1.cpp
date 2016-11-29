#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>	


int main(int argc, char *argv[]) {

	
	if(argc != 4)	{
		perror("Error en argumentos");
		exit(1);
	} else {

		int fd;

		char *doc;
		char *orden;
	
		orden = argv[1];
		doc = argv[3];

		if( (strcmp(argv[2], "<") == 0) ){

			fd = open (doc, O_RDONLY);
			close(0);
			if( fcntl( fd, F_DUPFD,0 ) == -1 ) perror ("Error fcntl");

		} else if ((strcmp(argv[2], ">") == 0)){
			
			fd = open (doc, O_CREAT|O_WRONLY);
			close (1);
			if( fcntl( fd, F_DUPFD, 1 ) == -1 ) perror ("Error fcntl");

		}
		
		
	        if( (execlp(orden, "", NULL) < 0)) {
			perror("Error en el execlp\n");
			exit(-1);
		}

		
		close(fd);

	}

}


