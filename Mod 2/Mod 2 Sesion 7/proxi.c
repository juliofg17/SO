/*#############################################################################

		JULIO A. FRESNEDA - juliofresnedaa17@gmail.com

##############################################################################*/





#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

#define tamano 1024
#define longnombre 50

// Método que asegura la exclusión mútua en pantalla
void ex_mutua	(int dbloqueo, int bloq) {
	
	struct flock cerrojo;
	
	cerrojo.l_type = bloq;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start= 0;
	cerrojo.l_len = 0;
	
	if (fcntl(dbloqueo, F_SETLKW, &cerrojo) == -1) {
		perror ("Error en exclusión mutua\n");
		exit(-1);
	}
}



int main( int argc, char* argv[] ){
	
	
	// Creación de archivo temporal
	FILE* temp = tmpfile();
	
	char buf[tamano];
		
	// Metemos en el archivo temporal los datos a imprimir
	int nbytes = read(STDIN_FILENO,buf,tamano);

	while( nbytes >= tamano ){

		fwrite(buf,sizeof(char),nbytes,temp);
		nbytes=read(STDIN_FILENO,buf,tamano);

	}
	
	fwrite(buf,sizeof(char),nbytes,temp);

	// Rebobinamos el current file offset	
	rewind(temp);

	// Leyemos los datos del archivo temporal, y los imprimimos en pantalla
	nbytes = fread(buf,sizeof(char),sizeof(buf),temp);
	
	ex_mutua(STDOUT_FILENO, F_WRLCK);		
	while( nbytes > 0 ){

		write(STDOUT_FILENO,buf,nbytes);
		nbytes = fread(buf,sizeof(char),sizeof(buf),temp);
	
	}

	printf("\nCliente %d ha acabado\n", getpid());
	ex_mutua(STDOUT_FILENO, F_UNLCK);
	char nombre[longnombre];
	sprintf(nombre, "fifo.%d", getpid());
	
	// Borramos el fifo de proxi temporal
	unlink(nombre);

	exit(0);
}

	
