#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
 #include <stdlib.h>




int main(int argc, char* argv[]){

	
	// Comprobación 
	if( argc!=2 ){
		printf("Introduce argumento\n");
		exit(-1);
	}

	//Paso del argumento a número entero
	int num = strtol(argv[1],NULL,10);
	pid_t PID;


	// Llamada a fork
	if( (PID = fork()) < 0 )
		printf("Error\n");

	// Código ejecutado por el proceso hijo
	if( PID == 0 ){
		if ( num%2 == 0 )
			printf("Argumento par (Proceso hijo)\n");
		else printf("Argumento impar (Proceso hijo)\n");
	}

	// Código ejecutado por el proceso padre
	else {
		if ( num%4 == 0 )
			printf("Argumento divisible entre 4 (Proceso padre)\n");
		else printf("Argumento indivisible entre 4 (Proceso padre)\n");
	}

	return 0;

}
		
	
