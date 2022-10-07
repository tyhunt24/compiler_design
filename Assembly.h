FILE *assemblyFile;

//load what we first get in the our Mips file
void initMipsFile() {
    assemblyFile = fopen("compiler.asm", "w");

    fprintf(assemblyFile, ".text\n");
    fprintf(assemblyFile, "main:\n");

    fclose(assemblyFile);
}

// Load what the value of each integer is into mips
void loadValueInts(char *id, char currentScope[50]) {
    assemblyFile = fopen("compiler.asm", "a");

    int var1 = found(id, currentScope);

    char *value1 = getValue(id, currentScope);
    printf("%s\n", value1);

    fprintf(assemblyFile, "li $t%d, %s\n", var1, value1);

    fclose(assemblyFile);
}

void loadValueIds(char *id1, char *id2, char currentScope[50]) {
    assemblyFile = fopen("compiler.asm", "a");
    
    int var1 = found(id1, currentScope);
    char *value1 = getValue(id2, currentScope);

    fprintf(assemblyFile, "li $t%d, %s\n", var1, value1);

    fclose(assemblyFile);
}


// Put the value of our addition into the compiler
void loadAddition(char *id, char currentScope[50]) {
    assemblyFile = fopen("compiler.asm", "a");

    int var1 = found(id, currentScope);

    char *value1 = getValue(id, currentScope);

    fprintf(assemblyFile, "li $t%d, %s\n", var1, value1);

    fclose(assemblyFile);
}


//I need to figure out how to get this to turn the right way.
void writeValue(char *id, char currentScope[50]) {
    assemblyFile = fopen("compiler.asm", "a");

    int var1 = found(id, currentScope);

    fprintf(assemblyFile, "li $v0, 1\n");
    fprintf(assemblyFile, "move $a0 $t%d\n", var1);
    fprintf(assemblyFile,"syscall\n");

    fclose(assemblyFile);
    }

//This prints what is at the end of the file.
void endMipsFile() {
    assemblyFile = fopen("compiler.asm", "a");

    fprintf(assemblyFile,"li $v0, 10\n");
    fprintf(assemblyFile,"syscall\n");
    fprintf(assemblyFile, ".end main\n");

    fclose(assemblyFile);
}



