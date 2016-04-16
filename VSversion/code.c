#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"


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

unsigned createMask(unsigned a, unsigned b)
{
   unsigned r = 0;
   for (unsigned i=a; i<=b; i++)
       r |= 1 << i;

   return r;
}



int decode (FILE * f)
{	
    int i;
    int numStructs = 1;
    long lSize; //tamanho do que foi lido no arquivo
    char * buffer;
   // int boolean; Será usado?
    unsigned int result;


    if(f == NULL)
    {
        printf("Erro na abertura do arquivo binario para leitura.\n");
        return -1;
    }
    
    for(i = 0; i < 20; i++) 
	{
        printf("-");
	}
	printf("\n");

    // obtém o tamanho do arquivo:
    fseek (f, 0 , SEEK_END);
    lSize = ftell (f);
    rewind (f);

    // aloca memória para o array buffer
    buffer = (char*) malloc (sizeof(char) * lSize);

    // copia o conteúdo do arquivo para dentro do array, nesse caso, result é usada também para checar se houve um erro
    // no caso, if(lSize == result) { printf("Erro na memoria.\n"); return -1;} 
    result = fread (buffer, 1, lSize, f);
     
    
    for(i = 0; i < result; i++) {
       //Aqui não sei se faz sentido, pois o for itera sobre o array, mas, e se forem varias estruturas? Em algum lugar esse IF tem que entrar
        if(buffer[i - 1] == NULL) {  //Se for a primeira estrutura do arquivo, estará no início do array, e o endereço anterior a ela será nulo
            printf("Estrutura %d", numStructs);    
    
            printf("\nMarca de início da estrutura.\n");
            
            // ^ 0xffffff00 aplica uma máscara no caso de ser 0x81 e 0x82, pois cada indice do array tem 4 bytes, 
            //como o compilador repete o bit mais significativo, talvez seja necessário fazer esse XOR, quando não for 01 ou 02
            if(((buffer[i + 1] ^ 0xffffff00) == 0x81) || buffer[i + 1] == 0x01) {
                printf("<int> ");       //printf("<int> 1"); p/ saber de onde veio 
                
            } else if(((buffer[i + 1] ^ 0xffffff00) == 0x82) || buffer[i + 1] == 0x02) {
                printf("<long> ");      //printf("<long> 1"); p/ saber de onde veio     
            } 
            i += 2; // ou i++; essa linha não serve para todos os casos de valores
            
            if(((buffer[i - 1] ^ 0xffffff00) == 0x81) || (buffer[i - 1] == 0x01)) {
            	// imprime a string valor int1, o 1 é um flag para saber de qual if ela veio, qnd se criar outros if com essa printf
                printf("valor int1\n");    // se o inteiro de 32bits ocupa no maximo 4 bytes, arrumar um jeito de ler até 4 posições do array
               // if(buffer[i] < valorMuitoGrande) { i += valorDeIncremento; } 
                i++;                         
            }
            
              if(((buffer[i - 1] ^ 0xffffff00) == 0x82) || (buffer[i - 1] == 0x02)) {
                printf("valor long1\n");                // para 64 bits, 8 posições no máximo 
                // if(buffer[i] < valorMuitoGrande) { i += valorDeIncremento; }
                i++;                        
            }
        }
        // aqui pode ser que 81 seja chave ou valor, então não rola 
      //  if(((buffer[i] ^ 0xffffff00)) == 0x81 || buffer[i] == 0x01 ) {
            
       // }
       
       
       
       
       
        
              
    }
     
    return 0;

}

