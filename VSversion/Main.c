#include <stdio.h>
#include "code.h"


typedef struct t{
    long l1;
	int i1;
} Teste;


int main (void)
{
	FILE * arq = fopen("output3.bin", "wb");
	Teste teste = { 123456789, 256 }; 
	
	code("li", &teste, arq);
   // decode(arq);
	fclose(arq);
	return 0;
}
