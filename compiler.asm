.text
main:
li $t1, 4
li $t2, 5
li $t3, 16
li $v0, 1
move $a0 $t3
syscall
li $v0, 10
syscall
.end main
