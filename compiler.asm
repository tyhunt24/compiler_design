.text
main:
	addi $a1, $zero, 100
	addi $a2, $zero, 300
jal add
li $v0, 1
move $a0 $v1
syscall
li $v0, 10
syscall
.end main
add:
	add $v1, $a1, $a2
	jr $ra
