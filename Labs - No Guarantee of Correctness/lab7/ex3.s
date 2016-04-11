/*int main(void)
{
	int val = 1;
	while(val <= 10)
	{	
		printf("%d\n", val*val);
		val++;
	}	

	return 0;
}*/


.data
Sf:  .string "%d\n"    /* string de formato para printf */

.text
.globl	main

main:


/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)  /* guarda rbx */
  movq    %r12, -16(%rbp)  /* guarda r12 */
/********************************************************/

  movl	  $1,  %eax	/* int val = 1 */	

L1:

  cmpl	  $10, %eax
  ja 	  L2

/*************************************************************/
/* este trecho imprime o valor do quadrado do valor em %eax e \n   */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl 	  %eax, %ebx
  imull	  %eax, %eax				
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
/*  movl    $0, %eax*/
  call    printf       /* chama a funcao da biblioteca */
/*************************************************************/
  movl	  %ebx, %eax
  inc   %eax		
  jmp	L1

L2:

/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq    -16(%rbp), %r12 /* recupera r12 */
  movq    -8(%rbp), %rbx  /* recupera rbx */
  leave
  ret      
/***************************************************************/

