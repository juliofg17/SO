#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <ftw.h>


int numarchivos = 0;
int tam = 0;



int entrar(const char* nombre, const struct stat * stat, int banderas, struct FTW* ftw) {

	if ((S_ISREG(stat->st_mode)) && (stat->st_mode & S_IXOTH) && (stat->st_mode & S_IXGRP) ) {

	    printf("%s %llu\n",path, stat->st_ino);

	    tam = tam + stat->st_size;
	    numarchivos++;

	}

	return 0; 
}



int main(int argc, char *argv[])
{

	printf("i-nodos:\n");
    
	
    if (nftw(argc > 1 ? argv[1] : ".", entrar, 10, 0) != 0) {
        perror("nftw");
    }

	
	printf("Hay %d archivos con permisos de ejecucion para grupo y otros\n",numarchivos);
	printf("El tamaño total es de %d bytes\n",tam);
 
	return 0; 

}
