#include <stdio.h>

unsigned char switch_byte(unsigned char x)
{
	unsigned char temp1 = x;
	unsigned char temp2 = x;
	temp1 = temp1 >> 4;
	temp2 = temp2 << 4;
	return (temp1 | temp2);
}


int main (void)
{
	printf("0x%x\n", switch_byte(0xab));

	return 0;

}
