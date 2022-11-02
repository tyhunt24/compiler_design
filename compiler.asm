.text
main:
jal add
li $v0, 1
move $a0 $t2
syscall
li $v0, 10
syscall
.end main
add:
	li $t2, 4
	jr $ra
