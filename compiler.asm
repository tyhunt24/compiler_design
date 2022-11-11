.text
main:
	addi $a0, $zero, 100
	addi $a1, $zero, 300
jal add
move $t5, $v1
li $v0, 1
move $a0 $t5
syscall
li $v0, 10
syscall
.end main
add:
	add $v1, $a0, $a1
	jr $ra
