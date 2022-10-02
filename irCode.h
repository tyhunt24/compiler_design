// ---- Functions to handle IR code emissions ---- //

void initIRcodeFile() {
    IRcode = fopen("IRcode.ir", "a");
}

void emitBinaryOperation(char op[1], const char* id1, const char* id2) {
    fprintf(IRcode, "T1 = %s %s %s", id1, op, id2);
}

void emitAssignment(char *id1, char *id2) {
    fprintf(IRcode, "%s = %s\n", id1, id2);

    fprintf(IRcode, "T1 = %s\n", id1);
    fprintf(IRcode, "T2 = %s\n", id2);
    fprintf(IRcode, "T3 = T1\n");
}

void emitConstantIntAssignment(char id1[50], char id2[50]) {
    fprintf(IRcode, "%s = %s\n" id1, id2);
}

void emitWriteId(char * id) {

    // We need to manage temporary variables
    // We need to implement a function that tells us which one instead of just T2.
    fprintf(IRcode, "output %s\n", "T2");
}