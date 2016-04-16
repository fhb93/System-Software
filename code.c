#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char key( char * desc, void * v, int i ) {
	char chave;
	int length;
	
	length = strlen(desc);														/* determina o comprimento da string desc */
	
    if(desc[i] == 'i') 															/* se o campo for inteiro */
    {
    	if(i == length - 1)
        	chave = 0x01;
        else 
        	chave = 0x81;
    }
                
    else            															/* se não, então o campo é long */	
    {	     
    	if(i == length - 1)
        	chave = 0x02;
        else 
        	chave = 0x82; 
     }
               
	return chave;
}

unsigned int ZigzagInt ( int n ) {
	unsigned int z = n;

	z = n << 1;

	if (n < 0)
		z = ~z;

	return z;
}

unsigned long ZigzagLong ( long n ) {
	unsigned long z = n;

	z = n << 1;

	if (n < 0)
		z = ~z;

	return z;
}

int code (char * desc, void * v, FILE * f) {
	int i, j = 0, varI, imp;
	char chave, init = 0xff;
	long varL;

	if(f == NULL) {																/* Erro de abertura de arquivo */
		printf("Erro na abertura do arquivo para escrita.\n");
		return -1;                                                              /* Retorna -1 */
	}

	fwrite(&init, sizeof(char), sizeof(init), f);								/* Imprime no arquivo binário a marca de início da estrutura */	

	for( i = 0; i < strlen(desc); i++ ) {
    	chave = key(desc, v, i);
    	fwrite( &chave, sizeof(char), sizeof(chave), f );
		
		if ( desc[i] == 'i' ) {
			varI = *( (int *) (v + j) );
			j += 4;
			varI = ZigzagInt(varI);

			if ( (i == 0) && (desc[i + 1] == 'l') )
				j += 4;
			else if (i < strlen(desc))
				if ( (i > 0) && ( (desc[i - 1] == 'l') && (desc[i + 1] == 'l') ) )
					j += 4;
	
			if ( varI != 0 ) {
				while ( varI != 0 ) {
					imp = varI & 0x7f;
					varI = varI >> 7;

					if ( varI != 0 )
						imp = imp | 0x80;

					fwrite(&imp, sizeof(char), sizeof(init), f);
				}
			}
			else {
				init = 0x00;
				fwrite(&init, sizeof(char), sizeof(init), f);
			}
				
		}
		else {
			varL = *( (long *) (v + j) );
			j += 8;
			varL = ZigzagLong(varL);
		
			if ( varL != 0 ) {
				while ( varL != 0 ) {
					imp = varL & 0x7f;
					varL = varL >> 7;

					if ( varL != 0 )
						imp = imp | 0x80;

					fwrite(&imp, sizeof(char), sizeof(init), f);
				}
			}
			else {
				init = 0x00;
				fwrite(&init, sizeof(char), sizeof(init), f);
			}
		}
	}
    
	return 0;
}





/*
int decode (FILE * f);
void value(void * v, char * arr)
{
  
 
    
}
*/
