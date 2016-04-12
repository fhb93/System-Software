#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int code (char * desc, void * v, FILE * f)
{
	int success = -1;
	char * chave; 
	char init[1] = {0xff};
        
        
	int len = 0;
	if(f == NULL)
	{
		printf("Erro na abertura do arquivo para escrita.\n");
		return success;                                                                          /* Retorna -1 */
	}
	len = strlen(desc);
    chave = (char*) malloc(sizeof(char)); 
    fwrite(init, sizeof(char), sizeof(init), f);       /* Imprime no arquivo binário a marca de início da estrutura */

    key(desc, chave, v);
    fwrite(chave, sizeof(char), len * sizeof(chave), f);
        
	success = 0;
	return success;
}



int decode (FILE * f);


void key(char * desc, char * arr, void * v)
{
	unsigned int length = 0;
    int i, j = 0;
	
	length = strlen(desc);			/* determina o comprimento da string desc */
	
	for(i = 0; i < length; i++)
        {
                if(desc[i] == 'i') /* se o campo for i */
                {
                        if(i == length - 1)
                        {
                                arr[j] = 0x01;
                        }
                        else {
                                arr[j] = 0x81; 
                        }
                       // arr[j+1] = zigzag((Teste*) v->i1);
                        arr[j+1] = 0xfc;
                        j += 2;
                }
                
                else            /* se não, então o campo é l */	
                {	
                 
                        if(i == length - 1)
                        {
                                arr[j] = 0x02;
                        }
                        else {
                                arr[j] = 0x82; 
                        }
                        
                        arr[j+1] = 0xfc;
                        arr[j+2] = 0xfc;
                        j += 3;
                        
                }
               
        }
}

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
