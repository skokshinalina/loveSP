.data
printf_format:
        .string "%d\n"
 
array:
        .long 3, 11, 15
array_end:
 
.text
.globl main
main:
        xorl %eax, %eax
        movl  $array, %ebx      
        jmp   ch_bound         
first:                    
        andl  $-33, (%ebx)     
        addl (%ebx), %eax
        addl  $4, %ebx
        cmpl  $array_end, %ebx  
        je    end_loop
second:        
        orl  $16, (%ebx)     
        addl (%ebx), %eax
        addl  $4, %ebx
        cmpl  $array_end, %ebx  
        je    end_loop
        jmp first                                   
ch_bound:
        cmpl  $array_end, %ebx  
        jne    first       
end_loop:
        pushl %eax
        pushl $printf_format
        call  printf
        addl  $8, %esp
 
        movl  $0, %eax
        ret
