.text
main:
jal add
li $v0, 1
move $a0 $t1
syscall
li $v0, 10
syscall
.end main
add:
	li $t1, 4
	jr $ra
