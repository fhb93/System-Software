#include <stdio.h>
#include "code.h"  

typedef struct t{
	int i1;
	long l1;	
} Teste;

int main (void)
{
	FILE * arq = fopen("output.bin", "wb");
    FILE * arq2 = fopen("output.bin", "rb");
	Teste teste = {1, 256}; //, {1,-1, 256, -256};
	
	//code("iil", &teste, arq);
	decode(arq2);
    fclose(arq);
    fclose(arq2);
	return 0;
}
