  .data
  nums: .int 3, -5, 7, 8, -2
  s1:   .string "%d\n"

  .text
  .globl main
  main:
  /* prologo */
     pushq %rbp
     movq  %rsp, %rbp
     subq  $16, %rsp
     movq  %rbx, -8(%rbp)
     movq  %r12, -16(%rbp)

     movq  $0, %rbx
     movq  $nums, %r12	
FOR:  
     cmpq  $5, %rbx
     je L2   
     
     movq  (%r12), %rdi
     movq $1, %rsi
     
     call filtro
     
     movq $s1, %rdi
     movl %eax, %esi
     movl $0, %eax
     call printf 

     addq $4, %r12
     addq $1, %rbx
     jmp FOR
L2:
  /* finalizacao */
     movq -8(%rbp), %rbx
     movq -16(%rbp), %r12
     leave
     ret

