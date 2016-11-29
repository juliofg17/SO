/*#############################################################################

		JULIO A. FRESNEDA - juliofresnedaa17@gmail.com

##############################################################################*/


#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>	

#define tamano 1024
#define longnombre 50


//Método para eliminar zombies
void sigchld_handler(int s)
{
    while(wait(NULL) > 0);
}




int main(int argc, char **argv){

	dup2(STDOUT_FILENO, STDERR_FILENO); // Ayuda a corregir errores


	// Declaración de variables
	int fde, fds;
	char nombrefifoe[longnombre], nombrefifos[longnombre];

	// Vaciamos el búffer
	setbuf(stdout, NULL);

	// Guardamos los nombres de entrada y salida del fifo servidor-cliente
	sprintf(nombrefifoe,"%se",argv[1]);
	sprintf(nombrefifos,"%ss",argv[1]);
	
	// Si ya existen fifos con esos nombres, los borramos	
	unlink(nombrefifoe);
	unlink(nombrefifos);


	// Creamos un fifo de entrada y otro de salida
	umask(0);
	
	if( mkfifo(nombrefifoe, 0777) != 0 ){
		perror("Error creando fifo entrada");
		exit(-1);
	}

	if( mkfifo(nombrefifos, 0777) != 0 ){
		perror("Error creando fifo salida");
		exit(-1);
	}

	printf("\nFifos creados\n");	
	
	

	// Conseguimos los file decriptor de los fifos antes creados	
	if( (fde = open(nombrefifoe,O_RDWR)) == -1 ){
		perror("Error abriendo fifo de entrada");
		exit(-1);
	}

	if( (fds = open(nombrefifos,O_RDWR)) == -1 ){
		perror("Error abriendo fifo de salida");
		exit(-1);
	}

	printf("Fifos abiertos\n");


	// Declaración de variables
	int nbytes;
	int buf[tamano];
	int pid;


	// Creación de proxi
	nbytes = read(fde,buf,sizeof(int));
	
	while( 1 ){
		
		pid = fork();
		if( pid == 0 ){

			printf("Creando proxi\n");
			
			int fd;
			char nombre[longnombre];
			
			int pid2 = getpid();
			
			sprintf(nombre, "fifo.%d", pid2);
		
			mkfifo(nombre,0777);

			printf("Fifo de proxi creado\n");

			if( (fd = open(nombre,O_RDWR)) == -1 ){
				perror("Error en open");
				exit(-1);
			}
			
			dup2(fd, STDIN_FILENO);

			write(fds,&pid2,sizeof(int));
			
			execl("./proxi","./proxi",NULL);
			
			perror("Error abriendo proxi");	

		}
		else if (pid > 0 ){
			
			nbytes = read(fde,buf,sizeof(buf));
	
			signal(SIGCHLD , sigchld_handler);
			

		}

	}


	exit(0);

}
			
	











