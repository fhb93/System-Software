#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char key( char * desc, void * v, int i )
{
	char chave;
	unsigned int length = 0;
	
	length = strlen(desc);			/* determina o comprimento da string desc */
	
    if(desc[i] == 'i') /* se o campo for i */
    {
    	if(i == length - 1)
        	chave = 0x01;
        else 
        	chave = 0x81;

        // arr[j+1] = zigzag((Teste*) v->i1);
        //arr[j+1] = 0xfc;
    }
                
    else            /* se não, então o campo é l */	
    {	     
    	if(i == length - 1)
        	chave = 0x02;
        else 
        	chave = 0x82; 
                        
		//arr[j+1] = 0xfc;
		//arr[j+2] = 0xfc;                        
     }
               
	return chave;
}

int code (char * desc, void * v, FILE * f)
{
	int len, i;
	char chave; 
	char init = 0xff;

	if(f == NULL)
	{
		printf("Erro na abertura do arquivo para escrita.\n");
		return -1;                                                                          /* Retorna -1 */
	}

	len = strlen(desc);

	fwrite(&init, sizeof(char), sizeof(init), f);
			/* Imprime no arquivo binário a marca de início da estrutura */

	for( i = 0; i < len; i++ ) {
    	chave = key(desc, v, i);
    	fwrite(&chave, sizeof(char), sizeof(chave), f);
	}
    
	return 0;
}



int decode (FILE * f);




void value(void * v, char * arr)
{
  
 
    
}

int zigzag(int n)
{
	unsigned int z = 0;
	//int tmp = n;

	z = n << 1;
	if(n < 0)
	{
		z = ~z;
	}
	return z;
}
