
	.text
	
	.globl	main
main:

	li	$v0,4		
	la	$a0, msg1	
	syscall

	li	$v0,8
    la $a0, string1
	syscall	

	la $s1, string1

	li $t1, 10						#newline
	li $t2, 32						#space
	li $t5, 0						#max length
	li $t6, 256						#min length
	move $t7, $s1					#max addr
	move $t8, $s1					#min addr
	loop:
	lb $t0, ($s1)					#string byte
	beq $t0, $zero, string_end		#check for newline
	li $t3, 0						#number of letters in current word
	move $t4, $s1					#current word
	word_loop:
	lb $t0, ($s1)
	beq $t2, $t0, word_end			#check for space
	beq $t1, $t0, word_end			#check for newline

	addi $t3, $t3, 1				#inc length of current word
	addi $s1, $s1, 1				#inc pointer
	j word_loop

	word_end:
	bgt $t3, $t5, new_max
	blt $t3, $t6, new_min
	sb $zero, ($s1)
	addi $s1, $s1, 1
	j loop

	new_max:
	move $t5, $t3
	move $t7, $t4
	sb $zero, ($s1)
	addi $s1, $s1, 1
	j loop

	new_min:
	move $t6, $t3
	move $t8, $t4
	sb $zero, ($s1)
	addi $s1, $s1, 1
	j loop


	string_end:

	li	$v0,4		
	la	$a0, msg2	
	syscall

	li	$v0,4		
	move	$a0, $t7
	syscall

	li	$v0,4		
	la	$a0, newline
	syscall

	li	$v0,4		
	la	$a0, msg3
	syscall

	li	$v0,4		
	move	$a0, $t8	
	syscall
	
	li	$v0,10		# exit
	syscall

.data
msg1:	.asciiz	"Enter the string:   "
msg2:	.asciiz	"The longest word is:   "
msg3:	.asciiz	"The shortest word is:   "
string1:   .space 256
newline:   .asciiz	"\n"