
	.text
	
	.globl	main
main:

	li	$v0,4		
	la	$a0, msg1	
	syscall

	li	$v0,5
	syscall	
	move	$t0,$v0	

	li	$v0,4
	la	$a0, msg2
	syscall

	li	$v0,5
	syscall	
	move	$t1,$v0	

	li $t2, 2
	li $t3, 0

	li		$v0, 4
	la	 	$a0, newline
	syscall

	loop1:
	div $t0, $t2
	mfhi $t4
	beq $t4, $t3, no
	addi $t2, $t2, 1
	beq	$t2, $t0, exitloop1
	j loop1
	exitloop1:

	li $t2, 2

	loop2:
	div $t1, $t2
	mfhi $t4
	beq $t4, $t3, no
	addi $t2, $t2, 1
	beq	$t2, $t1, exitloop2
	j loop2
	exitloop2:

	sub $t1, $t1, $t0
	li $t2, 2
	beq $t1, $t2, yes
	li $t2, -2
	beq $t1, $t2, yes
	j no

	yes:
	li	$v0,4		
	la	$a0, msg3
	syscall
	j exit

	no:
	li	$v0,4		
	la	$a0, msg4	
	syscall

	exit:
	li	$v0,10		# exit
	syscall

	.data
msg1:	.asciiz	"Enter the first number:   "
msg2:	.asciiz	"Enter the second number:   "
msg3:	.asciiz	"The numbers are twin prime.\n"
msg4:	.asciiz	"The numbers are not twin prime.\n"
newline:   .asciiz	"\n"