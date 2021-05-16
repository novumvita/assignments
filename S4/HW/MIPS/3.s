
	.text
	
	.globl	main
main:

	li	$v0,4		
	la	$a0, msg1	
	syscall

	li	$v0,8
    la $a0, string1
	syscall	

	li	$v0,4
	la	$a0, msg2
	syscall

	li	$v0,8
    la $a0, string2
	syscall	

    la $s1, finalStr  
    la $s2, string1  
    la $s3, string2

    li $t1, 10

    copyFirstString:  
    lb $t0, ($s2)                  # get character at address  
    beq $t0, $t1, copySecondString
    sb $t0, ($s1)                  # else store current character in the buffer  
    addi $s2, $s2, 1               # string1 pointer points a position forward  
    addi $s1, $s1, 1               # same for finalStr pointer  
    j copyFirstString              # loop  

    copySecondString:  
    lb $t0, ($s3)                  # get character at address  
    beq $t0, $t1, printString
    sb $t0, ($s1)                  # else store current character in the buffer  
    addi $s3, $s3, 1               # string2 pointer points a position forward  
    addi $s1, $s1, 1               # same for finalStr pointer  
    j copySecondString             # loop  

    printString:
    li	$v0,4		
	la	$a0, msg3	
	syscall

    li	$v0,4		
	la	$a0, finalStr	
	syscall


	li	$v0,10		# exit
	syscall


.data
msg1:	.asciiz	"Enter the first string:   "
msg2:	.asciiz	"Enter the second string:   "
msg3:	.asciiz	"The concatenated string is:    "
string1:   .space 256
string2:   .space 256
finalStr:   .space 256
newline:   .asciiz	"\n"