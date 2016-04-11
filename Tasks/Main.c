#include <stdio.h>
#include "code.h"  

typedef struct t{
	int i1;
	long l1;	
} Teste;





int main (void)
{
	FILE * arq = fopen("output.bin", "wb");
	Teste teste = {1, 256}; //, {1,-1, 256, -256};
	int res;
	
	
	res = code("iill", &teste, arq);
	fclose(arq);
	return 0;
}
