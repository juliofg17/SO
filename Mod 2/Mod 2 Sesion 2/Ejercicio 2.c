#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <unistd.h>


int main( int argc, char * argv[] ){

	// Comprobando si están los argumentos necesarios
	if( !argv[2] || !argv[1]  ){
		printf("Introduce argumentos\n");
		exit(-1);
	}

	   

	// Declaración de variables
	DIR *carpeta;
	struct dirent *archivos;
	struct stat info;
	int permisos_finales, permisos_antiguos;

	
	// Abriendo directorio
	carpeta = opendir(argv[1]);

	
	// Comprobando si se puede abrir
	if( carpeta == NULL ){
		printf("Error: No se puede abrir el directorio\n");
 		exit(2);	
	}


	
	printf("Se cambiarán los permisos de los archivos del directorio %s\n\n", argv[1]);
	printf("Permisos antiguos	Permisos nuevos\n");
	
	

	// Redirigiendo el puntero al inicio de la carpeta
	rewinddir(carpeta);
	
	
		
	// Operando uno por uno con los archivos de la carpeta 
	while ((archivos = readdir(carpeta)) != NULL) {
	chdir(argv[1]);
		
		// Guardando información del archivo, y los permisos antiguos y finales en variables
		if(stat(archivos->d_name,&info) < 0)
			printf("Error\n");
		else if(!S_ISDIR(info.st_mode)){
			permisos_finales = strtol(argv[2], 0, 8) & 0777;

			permisos_antiguos = info.st_mode & 0777;

			// Cambiando los antiguos permisos por los permisos finales del archivo	
			if (chmod(archivos->d_name, permisos_finales) < 0){
					
				printf("Error en %s", archivos->d_name);
					exit(-1); 

				} else {
			
					printf("%o			%o		Archivo: %s\n", permisos_antiguos, permisos_finales,archivos->d_name);

				}
			
		}

		
	}
	
	// Cerrando carpeta, programa finalizado
	closedir(carpeta);

	




return 0;
}

	
