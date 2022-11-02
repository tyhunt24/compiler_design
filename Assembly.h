/*
Need to add functionality to deal with functions
Also need to add functionlity to deal with arrays
*/
FILE *assemblyFile;

int numParams = 0;

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

//load in the ids into mips
void loadValueIds(char *id1, char *id2, char currentScope[50]) {
    assemblyFile = fopen("compiler.asm", "a");
    
    int var1 = found(id1, currentScope);
    char *value1 = getValue(id2, currentScope);

    fprintf(assemblyFile, "li $t%d, %s\n", var1, value1);

    fclose(assemblyFile);
}


// Put the value of our addition into the compiler
// Call this in the id = expression so it gives us the correct expression
void loadAddition(char *id, char currentScope[50]) {
    assemblyFile = fopen("compiler.asm", "a");

    int var1 = found(id, currentScope);

    char *value1 = getValue(id, currentScope);

    fprintf(assemblyFile, "\tli $t%d, %s\n", var1, value1);

    
}


//Code to print the value to the screen
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


void MipsCreateFunction(char label[50]) {
    assemblyFile = fopen("compiler.asm", "a");
    
 
    fprintf(assemblyFile, "%s:\n", label);
}

void mipsJumpFunction(char label[50]) {
    assemblyFile = fopen("compiler.asm", "a");
    
 
    fprintf(assemblyFile, "jal %s\n", label);

    fclose(assemblyFile);
}

void mipsInside() {
    assemblyFile = fopen("compiler.asm", "a");
    
 
    fprintf(assemblyFile, "\tjr $ra\n");
}

void addMips() {
    assemblyFile = fopen("compiler.asm", "a");
    
 
    fprintf(assemblyFile, "\tadd $v1, $a1, $a2\n");
}

void paramMips() {
    assemblyFile = fopen("compiler.asm", "a");
    
 
    fprintf(assemblyFile, "\taddi $a1, $zero, 2\n");

    fclose(assemblyFile);
}



