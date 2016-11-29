#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {

	
	struct flock cerrojo;
	int fd, i;

	if( argc != 2 ) {
		printf("Error en argumentos");
		exit(1);

	} else {

		char *doc = argv[1];

		if( (fd=open(doc, O_RDWR)) < 0 ){
			perror("Error en el archivo");
			return 0;
		}

		cerrojo.l_start=0;
		cerrojo.l_type=F_WRLCK;
		cerrojo.l_len=0;
		cerrojo.l_whence=SEEK_SET;

		fcntl (fd, F_SETLKW, &cerrojo);

		printf("Archivo bloqueado\n");
		sleep(5);
	


		cerrojo.l_start=0;
		cerrojo.l_type=F_UNLCK;
		cerrojo.l_len=0;
		cerrojo.l_whence=SEEK_SET;

		fcntl (fd, F_SETLKW, &cerrojo);

		printf("Archivo desbloqueado\n");
		
		return 0;
	}
}

