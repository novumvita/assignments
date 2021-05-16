
	.text
	
	.globl	main
main:

	li	$v0,4		
	la	$a0, msg
	syscall

    li	$v0,8
    la $a0, string
	syscall	

    li	$v0,4		
	la	$a0, msgword
	syscall

    li	$v0,8
    la $a0, word
	syscall	

    li	$v0,4		
	la	$a0, msgreplacement
	syscall

    li	$v0,8
    la $a0, replacement
	syscall	

    li $t0, 10      #newline
    li $t1, 32      #space
    la $s0, string
    la $t2, string  #current word
    la $s1, stringnew

    string_loop:
    lb $t3, ($s0)
    beq $t3, $zero, end_string_loop     #check for null
    beq $t3, $t0, word_end              #check for newline
    beq $t3, $t1, word_end              #check for space
    j not_word_end

    word_end:
    sb $zero, ($s0)                     #null terminate word
    la $t4, word                        #word to be replaced
    move $t5, $t2                       #current word

    word_loop:
    lb $t6, ($t4)
    lb $t7, ($t5)
    beq $t6, $t0, isequal               #end of word to be replaced
    bne $t6, $t7, not_equal
    addi $t4, $t4, 1
    addi $t5, $t5, 1
    j word_loop

    isequal:
    beq $t7, $zero, equal		 #end of current word also, so equal
    bne $t7, $zero, not_equal

    equal:
    la $t6, replacement                 #write replacement
    j word_write

    not_equal:
    move $t6, $t2                       #write current word
    j word_write

    word_write:
    lb $t7, ($t6)                       #write t6 to s1
    beq $t7, $zero, end_write
    beq $t7, $t0, end_write
    sb $t7, ($s1)
    addi $t6, $t6, 1
    addi $s1, $s1, 1
    j word_write
    end_write:

    sb $t1, ($s1)                       #space for newstring
    addi $s1, $s1, 1
    move $t2, $s0                       #current word   
    addi $t2, $t2, 1

    not_word_end:
    addi $s0, $s0, 1
    j string_loop
    end_string_loop:

    addiu $s1, $s1, -1
	sb $zero, ($s1)
	
	li $v0, 4
	la $a0, msgnew
	syscall
	
	li $v0, 4
	la $a0, stringnew
	syscall
	
	li $v0, 4
	la $a0, newline
	syscall
	
	li $v0,10
	syscall

	.data
msg: .asciiz "Enter string: "
msgword: .asciiz "Enter word to replace: "
msgreplacement: .asciiz "Enter word to be replaced with: "
msgnew: .asciiz "Resultant string is: "
string: .space 100
word: .space 50
replacement: .space 50
stringnew: .space 100
newline: .asciiz "\n"
