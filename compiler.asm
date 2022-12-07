.text
main:
li $t1, 9
li $t2, 4
blt $t1, $t2, IfStmt
j ElseStmt
Exit: 
	li $v0, 10
	syscall
	.end main
ElseStmt:
	li $v0, 1
	move $a0 $t1
	syscall
	j Exit
IfStmt:
	li $v0, 1
	move $a0 $t2
	syscall
