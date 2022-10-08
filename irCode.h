// ---- Functions to handle IR code emissions ---- //
#include <string.h>
#include <stdio.h>
FILE *IRcode;

// ! Also I need to figure out how to just clean the IR code up.

void initIRcodeFile() {
    IRcode = fopen("IRcode.ir", "a");

    fclose(IRcode);
}

//write the assignment 
void emitAssignment(char id1[50], char id2[50], char currentscope[50]) {
  
  // Open the value to be used in IR code
   IRcode = fopen("IRcode.ir", "a");
    int var1 = found(id1, currentscope);
  //This returns the the Var ID I actually think
  //I want it to return the ids value
   char* var2 = getValue(id2, currentscope);

   fprintf(IRcode, "T%d = %s\n", var1, var2);
   
   fclose(IRcode);
}

 void emitConstantIntAssignment(char id1[50], char num[50], char currentScope[50]) {
   FILE *IRcode;
   IRcode = fopen("IRcode.ir", "a");
  
  int var1 = found(id1, currentScope);

     fprintf(IRcode, "T%d = %s\n", var1, num); // What we want it to look like

     fclose(IRcode);
 }

// ! We dont need this because I do constant folding within the parser
// This elimnates the need to add these values here
//  void emitBinaryOperation(char op[1], char id1[50], char id2[50]) {

//        FILE *IRcode;
//        IRcode = fopen("IRcode.ir", "a");
//     fprintf(IRcode, "T1 = %s %s %s\n", id1, op, id2); // We need to figure out a way on how to mange the Temporary registers
//  }

void emitWriteId(char id[50], char currentScope[50]) {
        FILE *IRcode;
       IRcode = fopen("IRcode.ir", "a");

       int var1 = found(id, currentScope);
     fprintf(IRcode, "output T%d\n", var1);

     fclose(IRcode);
 }