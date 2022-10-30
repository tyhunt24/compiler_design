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

void emitFunctionAssignment() {
  printf("Null"); 
}

//assign a value to the Integer
 void emitConstantIntAssignment(char id1[50], char num[50], char currentScope[50]) {
   FILE *IRcode;
   IRcode = fopen("IRcode.ir", "a");
  
  int var1 = itemIndex(id1, currentScope);

     fprintf(IRcode, "T%d = %s\n", var1, num); // What we want it to look like
 }

//Write the Id to the IR code
void emitWriteId(char id[50], char currentScope[50]) {
        FILE *IRcode;
       IRcode = fopen("IRcode.ir", "a");

       int var1 = itemIndex(id, currentScope);
     fprintf(IRcode, "output T%d\n", var1);

     fclose(IRcode);
 }

 void IRFunctionCall(char label[50]) {
       FILE *IRcode;
       IRcode = fopen("IRcode.ir", "a");

       fprintf(IRcode, "goto %s\n", label);

       fclose(IRcode);
      
 }

 void labelFunction(char label[50]) {
       FILE *IRcode;
       IRcode = fopen("IRcode.ir", "a");
       
       fprintf(IRcode, "%s:\n", label);

       fclose(IRcode);
 }
 