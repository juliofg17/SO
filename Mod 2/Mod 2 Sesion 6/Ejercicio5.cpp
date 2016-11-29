#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>	
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>


int main(int argc, char *argv[]) {

	
	if(argc != 3) {
		
		printf("Error en argumentos\n");
		exit(1);

	} else {

		
        	struct stat s;
		int tam;
	
		char *src = argv[1];
		char *dest = argv[2];
	
		int fd_src, fd_dest;
		char *mem_src, *mem_dest;
	
		fd_src = open(src, O_RDONLY);

 		fstat (fd_src, &s);

                if (!S_ISREG (s.st_mode)) {
                	printf ("Fichero no regular\n");
               		return 1;
      		}

       	        tam = s.st_size;
		
		umask(0);
		fd_dest = open(dest, O_RDWR|O_CREAT|O_EXCL, S_IRWXU);
		if (fd_dest == -1) {
			perror("Error en archivo de salida\n");
			exit(2);
		}  

		ftruncate(fd_dest, tam);

		mem_src = (char *) mmap(0, tam, PROT_READ, MAP_SHARED, fd_src, 0);
		if(mem_src == MAP_FAILED) {

			perror("Error en mmap");
			exit(2);
		}

		mem_dest = (char *) mmap(0, tam, PROT_WRITE, MAP_SHARED, fd_dest, 0);
		if(mem_dest == MAP_FAILED) {
			
			perror("Error en mmap");
			exit(2);

		}
		
		memcpy(mem_dest, mem_src, tam);
		munmap(mem_src, tam);
		munmap(mem_dest, tam);

		close(fd_src);
		close(fd_dest);

		return 0;


	}

}
