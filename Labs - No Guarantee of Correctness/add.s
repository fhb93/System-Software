/*
int add (int a, int b, int c) {
  return a+b+c;
}
*/

.text
.globl	add

add:
	movl	%esi,	%eax
	addl	%edi,	%eax
	addl	%edx,	%eax
	
	ret
