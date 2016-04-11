#include <stdio.h>

int odd_ones(unsigned int x)
{
	int i, sum = 0;
	unsigned int tst = x; 
	for(i = 0; i < 32; i++)
	{
		sum += (tst & 1);
		tst = x >> (i + 1);
	}

	if(sum & 1)
	{
		return 1;
	}

	return 0;	

}

int main (void)
{
 	//int par = 0x01010101;
	int impar = 0x01030101;
	printf("%d", odd_ones(impar));
	return 0;
}
