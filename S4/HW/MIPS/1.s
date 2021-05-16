
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

	li $t1, 1
	li $t2, 1
	li $t3, 1

	li		$v0, 1
	move	$a0, $t1
	syscall
	li		$v0, 4
	la	 	$a0, newline
	syscall
	loop:
	li		$v0, 1
	move	$a0, $t2
	syscall
	li		$v0, 4
	la	 	$a0, newline
	syscall
	move $t4, $t2
	add $t2, $t1, $t2
	move $t1, $t4
	addi $t3, $t3, 1
	beq	$t3, $t0, exit
	j loop

	exit:
	li	$v0,10		# exit
	syscall

	.data
msg1:	.asciiz	"Enter n:   "
msg2:	.asciiz	"The first n Fibonacci numbers are: \n"
newline:   .asciiz	"\n"