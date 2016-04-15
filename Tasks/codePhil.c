#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
char key( char * desc, void * v, int i ) {
	char chave;
	int length;
	
	length = strlen(desc);			// determina o comprimento da string desc 
	
    if(desc[i] == 'i') /* se o campo for i
    {
    	if(i == length - 1)
        	chave = 0x01;
        else 
        	chave = 0x81;

        // arr[j+1] = zigzag((Teste*) v->i1);
        //arr[j+1] = 0xfc;
    }
                
    else             se não, então o campo é l 
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
*/
/*
long Zigzag ( long n ) {
	long z;

	z = n << 1;

	if (n < 0)
		z = ~z;

	return z;
}

int VerificaTipo ( void * v, int length ) {
	if ( length * 4 == sizeof(v) )
		return 4;
	else
		return 8;
}

long SeparaVariavel ( void * v, int i, int var, int len ) {
	long ret;
	void * temp = v;

	if ( i > 0 )
		temp = temp << ( i * var * 8 );
	else if ( i < len )
		temp =  temp >> (( sizeof(v) - var ) * ( i * var * 8 ));

	ret = (long) temp;

	return ret;
}

int code (char * desc, void * v, FILE * f) {
	int len, i;
	char chave; 
	char init = 0xff;

	if(f == NULL)
	{
		printf("Erro na abertura do arquivo para escrita.\n");
		return -1;                                                                          // Retorna -1 
	}

	len = strlen(desc);

	fwrite(&init, sizeof(char), sizeof(init), f);
			// Imprime no arquivo binário a marca de início da estrutura 

	for( i = 0; i < len; i++ ) {
    	chave = key(desc, v, i);
    	fwrite(&chave, sizeof(char), sizeof(chave), f);

		
	}
    
	return 0;
}
*/


int decode (FILE * f)
{
    char * arr;
    int fSize, result, i;
    
    if(f == NULL) 
    {
        printf("Erro na abertura do arquivo binario para leitura.\n");
        return -1;
    }
    fseek(f, 0, SEEK_END);
    fSize = ftell(f);
    
    arr = (char*) malloc(sizeof(char) * fSize);
    
    result = fread(arr, 1, fSize, f);
    
    if(result != fSize)
    {
        printf("Erro de leitura.\n");
        return -1;
    }
    
    for(i = 0; i < strlen(arr); i++) 
    {
        printf("%x", arr[i]);
    }
    return 0;
    
}



/*
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
*/
