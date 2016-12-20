// APELLIDOS: FRESNEDA GARCÍA
// NOMBRE: JULIO ANTONIO 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>

int main( int argc, char* argv[] ){
	



	if( argc != 2 ){
		printf("Numero incorrecto de argumentos.\n");
		exit(-1);
	}

	char ruta[NAME_MAX];
	sprintf(ruta,"%s.tipo",argv[1]);

	printf("%s",ruta);

	umask(0);
	mkdir(ruta,0777);

	DIR* dir;
	if( (dir = opendir(argv[1])) == NULL ) {
		perror("Error abriendo directorio");
		exit(-1);
	}

	DIR* dir_ruta;
	if( (dir_ruta = opendir(ruta)) == NULL ) {
		perror("Error abriendo directorio");
		exit(-1);
	}
		
	
	struct dirent* nombres;
	pid_t pid;
	int fd[2];
	int fdaux;
	int tam;
	int wait_int;
	
	char user[NAME_MAX];
	char rutaaux[NAME_MAX];
	char argaux[NAME_MAX];
	char buffer[PATH_MAX];
	struct stat atrib;
	
	while( (nombres = readdir(dir)) != NULL ){
		if( !(nombres->d_name[0] == '.' && nombres->d_name[1] == '\0') &&  !(nombres->d_name[0] == '.' && nombres->d_name[1] == '.' && nombres->d_name[2] == '\0') ){
			if( pipe(fd) < 0 ){
				perror("Error en pipe");
				exit(-1);
			}

			
			if( (pid = fork()) == -1 ){
				perror("Error en fork");
				exit(-1);
			}
		

			if( pid == 0 ){
				close(fd[0]);
				dup2(fd[1],STDOUT_FILENO);
				sprintf(argaux,"%s/%s",argv[1],nombres->d_name);
				execl("/usr/bin/file","file",argaux,NULL);
			}

			else{
				close(fd[1]);
				sprintf(rutaaux,"%s/%s.tipo",ruta,nombres->d_name);
				
				if( (fdaux = open(rutaaux,O_CREAT|O_RDWR,0777)) == -1){
					perror("Error en open");
					exit(-1);
				}
				tam = read(fd[0],buffer,PATH_MAX);
				
				if( write(fdaux,buffer,tam) < 0 ){
					printf("Error en write");
					exit(-1);
				}
				stat(argaux,&atrib);
				
				if( atrib.st_mode |  S_ISUID )
					write(fdaux,"\nSUID: true",11);
				else write(fdaux,"\nSUID: false",12);

				sprintf(user,"\nUser ID: %u",atrib.st_uid);
				write(fdaux,user,strlen(user));
				
				
				waitpid(-1,&wait_int,WUNTRACED);
				if( !WIFEXITED(wait_int) )
					printf("El hijo %u terminó inesperadamente",pid);
				
				
				
			}
		}
	}

}
		
			
				
			













			
			
	

