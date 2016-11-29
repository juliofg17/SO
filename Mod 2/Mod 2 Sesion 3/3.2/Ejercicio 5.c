#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){

	pid_t valorfork[5];
	int * status;
		
		if( (valorfork[0] = fork()) == -1 )
			printf("Error\n");
		
		if( !valorfork[0] ){
			printf("Soy el hijo %d\n",getpid());
		
		}

		if( valorfork[0] ){
			
			
			if( (valorfork[1] = fork()) == -1 )
				printf("Error\n");

			if( !valorfork[1] ){
				printf("Soy el hijo %d\n",getpid());
				
			}

			if( valorfork[1] ){
				
				if( (valorfork[2] = fork()) == -1 )
					printf("Error\n");
				
				if( !valorfork[2] ){
					printf("Soy el hijo %d\n",getpid());
					
				}

				if( valorfork[2] ){
					
					if( (valorfork[3] = fork()) == -1 )
						printf("Error\n");

					if( !valorfork[3] ){
						printf("Soy el hijo %d\n",getpid());
						
					}
	
					if( valorfork[3] ){
						
						if( (valorfork[4] = fork()) == -1 )
							printf("Error\n");
	
						if( !valorfork[4] ){
							printf("Soy el hijo %d\n",getpid());
							
						
						}

					}
				}
			}
		}
	

	int c = 5;
	for (int i = 0;i<3;i++) {

		if (waitpid(valorfork[2*i],0,0) > 0) {                  
			c--;
	    		printf("Acaba de finalizar mi hijo con PID:%d\n",valorfork[i]);
	    		printf("Solo me quedan %d hijos vivos\n",c);
      
    	}
}
for (int i = 0;i<3;i++) {

		if (waitpid(valorfork[2*i+1],0,0) > 0) {                  
			c--;
	    		printf("Acaba de finalizar mi hijo con PID:%d\n",valorfork[i]);
	    		printf("Solo me quedan %d hijos vivos\n",c);
      
    	}
}
	

	return(0);
}
