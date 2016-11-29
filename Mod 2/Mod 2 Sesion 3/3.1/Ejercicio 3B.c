#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){

	pid_t valorfork;
	int * status;
	for( int i=0; i<20; i++ ){
		
		// Creación del hijo
		if( (valorfork = fork()) == -1 )
			printf("Error\n");

			
		// Si es el padre
		if( valorfork )
			printf("PID Padre: %d\n",getpid());

		// Si es el hijo
		else printf("PID Hijo: %d\n\n",getpid());

		// Matando al proceso padre
		if( !valorfork )
			break;

	wait(status);
	}

	return(0);
}
