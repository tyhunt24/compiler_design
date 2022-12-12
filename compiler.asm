.text
main:
li $t1, 0
li $t2, 10
WhileStmt:
bgt $t1, $t2, Exit
	li $v0, 1
	move $a0 $t1
	syscall
addi $a0, $0, 0xA
addi $v0, $0, 0xB
syscall
add $t1, $t1, 1

j WhileStmt
Exit: 
	li $v0, 10
	syscall
	.end main
