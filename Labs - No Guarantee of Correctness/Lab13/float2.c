#include <stdio.h>
#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff))
#define getsig(x)  ((x)>>31 & 1)
#define getexp(x)  ((x)>>23 & 0xff)
#define getfrac(x) ((x) & 0x7fffff)

typedef union { 
  float f;
  unsigned int i;
 } U;

U u;

float float2(float f)
{
	unsigned int u1;
	unsigned int sig, exp, frac;
	u.f = f;

	sig = getsig(u.i);
	exp = getexp(u.i);
	frac = getfrac(u.i);
	exp <<= 1;
	exp |= 0x80;

	u1 = makefloat(sig, exp, frac);
	u.i = u1;

	return u.f;
}

int main ( void )
{
	float f1 = 5.5;
	printf("x2 = %.2f %x\n", float2(f1), u.i);
	return 0;
}
