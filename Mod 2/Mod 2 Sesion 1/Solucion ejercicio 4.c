#include <sys/stat.h>
#include <stdio.h>
#define ESREGULAR(FILE) S_ISREG(FILE.st_mode)

int main(int argc, char *argv[]){
struct stat atributo;
lstat(argv[1],&atributo);

if(ESREGULAR(atributo)){
	printf("\nEs regular");
}else printf("\nNo es regular");

return 0;
}
