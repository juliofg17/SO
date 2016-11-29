#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	
int fd1;

if(!argv[1])			// Si utilizamos la entrada estándar
	fd1 = 0;
else{	
				// Si como entrada usamos un argumento
if( (fd1 = open(argv[1],O_RDONLY)) < 0) {
	printf("\nError %d en open",errno);
	perror("\nError en open");
	exit(-1);
}
}


int fd2;

				// Creamos un archivo de texto llamado "Resultado.txt"
if( (fd2 = open("Resultado.txt",O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR)) < 0){
	printf("\nError %d en open",errno);
	perror("\nError en open");
	exit(-1);
}

char buffer[80];
int c=0;

while(read(fd1,buffer,80)>0){  // Operamos para que en el archivo "Resultado.txt" aparezcan los datos de entrada en bloques de 80 bytes
	
	dprintf(fd2,"Bloque %d",c);
	write(fd2,"\n",1);
	write(fd2,buffer,80);
	write(fd2,"\n\n\n",3);
	c++;
	
}

close(fd1);
close(fd2);

return 0;

}
