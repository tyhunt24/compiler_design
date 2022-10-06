%{
/*
Where I am at:
    - I am able to print the correct assembly code to a file for addition

Things I need to add:
   - In mips I need to have two write statements
   - I need to figure out how to produce the correct IR code
        - Once I figure that out we can start optimizations
   - I need to figure out how to plan with Memory Allocation

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbolTable.h"
#include "AST.h"
#include "IrCode.h"
#include "Assembly.h"

extern int yylex();
extern int yyparse();

extern FILE* yyin;

void yyerror(const char* s);
char currentScope[50];

int semanticChecks = 1;

%}

%union {
    int number;
    char character;
    char* string;
    struct AST* ast;
}

%token <string> TYPE
%token <string> ID
%token <char> SEMICOLON
%token <char> EQ
%token <char> OP
%token <number> NUMBER
%token WRITE

%printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } NUMBER;

%type <ast> Program DeclList Decl VarDecl StmtList Stmt Expr Addition

%start Program

%%
Program: DeclList   {$$ = $1;
                        endMipsFile();
                    }

;

DeclList:   Decl DeclList   {$1->left = $2;
                             $$ = $1;
                            }
    | Decl  { $$ = $1; }  
;

Decl: VarDecl
    | StmtList
;

VarDecl:    TYPE ID SEMICOLON {printf("\n RECOGNIZED RULE: VARIABLE DECLERATION\n");
                             $$ = AST_assignment("Type", $1, $2);
                             //Show that we have access to symbol table
                             int insymTab = found($2, currentScope);
                            
                            //--------------- Semantic Checks ------------------
                            if (insymTab == 0) 
                                addItem($2, "Var", $1, 0, currentScope); //if not in the symbol table add it
                                
                            else
                                printf("Semantic Error: Var %s is already in the symbol table", $2);
                            
                            // print what the symbol table looks like
                            showSymTable();

                        }
;

StmtList: Stmt  
        | Stmt StmtList
;

Stmt: Expr SEMICOLON
;

Expr:   Addition {printf("\nRECOGNIZED RULE: Primary Statement\n");
                    $$ = $1;

                }
    |   ID EQ ID {printf("\nRECONGINZED RULE: Assignment statement\n");
                    $$ = AST_assignment("=", $1, $3);

                    //updates our value in the Symbol Table
                    updateValue($1, currentScope, getValue($3, currentScope));

                    //------------- Semantic Checks ----------------//
                    int semanticChecks = 1;
                    if(found($1, currentScope)  == 0) {
                        printf("Semantic Error: %s is not intialized\n", $1);
                        semanticChecks = 0;
                    }

                    if(found($3, currentScope)  == 0) {
                        printf("Semantic Error: %s is not intialized\n", $3);
                        semanticChecks = 0;
                    }

                    //checks to make sure they are the correct type
                    if (compareTypes(found($1, currentScope), found($3, currentScope) == 0)) {
                        printf("Semantic Error: Variables %s and %s type mismatch\n", $1, $3);
                        semanticChecks = 0;
                    }

                    if(semanticChecks == 1) {
                        //printf("\nAll Semantics Check passed");
                        emitAssignment($1, $3, currentScope);  //Send IR code to seperate file



                    }
                 }

    |   ID EQ NUMBER {printf("\n RECONGIZED RULE: Number Decleration\n");
                        char str[50];
                        sprintf(str, "%d", $3);
                        $$ = AST_assignment("=", $1, str);
                        

                        // ------------- Semantic Checks ----------------//
                        if(found($1, currentScope) == 0) {
                            printf("Error: Variable %s not found", $1);
                            semanticChecks = 0;
                        }

                        //checks to make sure that ID is an Integer.
                        if (strcmp(getVariableType($1, currentScope), "int") != 0) {
                            printf("Error: Variable %s not found", $1);
                            semanticChecks = 0;
                        } 

                        //check if the statement is redundant
                            // ! Make sure it does not print as IR code
                        //change number to str

                       //updates value to the symbol table
                       updateValue($1, currentScope, str);

                            if (semanticChecks == 1) {
                            printf("All Semantic Checks passed\n");

                            // ! works for now need to make some changes
                            emitConstantIntAssignment($1, str, currentScope);

                            //put what our value is into mips
                            loadValueInts($1, currentScope);
                       }
                    }

    | ID EQ Addition {printf("\nRecongized Rule: Math Expression\n");
                        //AST Tree: =: head, $1: left, $3: right
                        $$ = idMathexp("=", $1, $3);

                        // -------- Semantic Checks --------- //
                        // Need to check to make sure that ID is an Int
                        if (strcmp(getVariableType($1, currentScope), "int") != 0) {
                            printf("Error: Variable %s not found", $1);
                            semanticChecks = 0;
                        } 

                        //update our value after addition is performed
                        updateValue($1, currentScope, $3->nodeType);
                        if($3->isNumber == 1) {
                            
                            //put value into IR code file
                            emitConstantIntAssignment($1, $3->nodeType, currentScope);

                            //puts this into our mips file
                            loadAddition($1, currentScope);
                        }
                }
                        
    |   WRITE ID {printf("\nRECONGIZED RULE: Print Statement\n");
                    $$ = AST_Write("Write", $2, "");
                    emitWriteId($2, currentScope);
                    writeValue($2, currentScope);
                }
;

Addition: Addition OP Addition {printf("\nReconiged Rule: Addition Expression\n");
                                int num1 = atoi($1->nodeType);
                                int num2 = atoi($3->nodeType);

                                //check to make sure both expressions are numbers
                                if ($1->isNumber && $3->isNumber == 1) {
                                    int number = num1 + num2; // add the two numbers together

                                    //convert our int back into a number
                                    char str[50];
                                    sprintf(str, "%d", number);

                                    //copy them into first node
                                    strcpy($1->nodeType, str);

                                    //create a new subtree
                                    struct AST *n = newTree($1->nodeType, NULL, NULL);
                                    n->isNumber = 1;
                                    $$ = n; // push that subtree so Bison takes care of it.


                                    //Generate IR code
                                   // emitBinaryOperation("+", $1->nodeType, $3->nodeType);

                                }   
                                    //If only the first number is a 1
                                    else if($1->isNumber == 1) {
                                        
                                        //get the number values of the two values
                                        int num1 = atoi($1->nodeType);
                                        char *val1 = getValue($3->nodeType, currentScope);
                                        int num2 = atoi(val1);

                                        //add the numbers together
                                        int number = num1 + num2; 

                                        //transform our number into a character
                                        char str[50];
                                        sprintf(str, "%d", number);
                                        strcpy($1->nodeType, str);

                                        //put that back into our AST.
                                        struct AST *n = newTree($1->nodeType, NULL, NULL);
                                        n->isNumber = 1;
                                        $$ = n; 

                                    //Generate IR code
                                    //emitBinaryOperation("+", $1->nodeType, $3->nodeType);

                                    } 
                                        else if($3->isNumber == 1) {
                                        int num1 = atoi($3->nodeType);
                                        char *val1 = getValue($1->nodeType, currentScope);

                                        int num2 = atoi(val1);

                                        int number = num1 + num2; 

                                        char str[50];
                                        sprintf(str, "%d", number);
                                        strcpy($1->nodeType, str);

                                        struct AST *n = newTree($1->nodeType, NULL, NULL);
                                        n->isNumber = 1;
                                        $$ = n; 

                                        //Generate IR code
                                    //emitBinaryOperation("+", $1->nodeType, $3->nodeType);

                                    }

                                    else {
                                        //IF the values are variables instead of numbers
                                        char *val1 = getValue($1->nodeType, currentScope); //get what the values are
                                        char *val2 = getValue($3->nodeType, currentScope); //get the values

                                        //Change them into numbers and add them
                                        int num1 = atoi(val1);
                                        int num2 = atoi(val2);
                                        int number = num1 + num2;

                                        //Change it back into a string
                                        char str[50];
                                        sprintf(str, "%d", number);
                                        strcpy($1->nodeType, str);

                                        //add it back into our AST
                                        struct AST *n = newTree($1->nodeType, NULL, NULL);
                                        n->isNumber = 1;
                                        $$ = n; 

                                    //Generate IR code
                                    //emitBinaryOperation("+", $1->nodeType, $3->nodeType);
                                }
                               
                            }
        | ID {printf("\n ID\n");
            // Checks to make sure the ID is has already been declared
            if(found($1, currentScope) == 0) {
                printf("SemanticError: %s is not found\n", $1);
            }

            if (strcmp(getVariableType($1, currentScope), "int") != 0) {
                    printf("Error: Variable %s is not of Type of int", $1);
                    semanticChecks = 0;
                        } 
            
            //Puts our id in the AST
            struct AST *num = newTree($1, NULL, NULL);
            $$ = num;
        }

       
    | NUMBER {printf("\n In Number\n");
        char str[50];
        sprintf(str, "%d", $1);
       struct AST * num = newTree(str, NULL, NULL); // put the number into the bottom of the tree

        num->isNumber = 1; // keeps track of when something becomes a number

        $$ = num; //constructs our subtree back into the main tree
    }

;

%%


int main(int argc, char**argv)
{
	// #ifdef YYDEBUG
	// 	yydebug = 1;
	// #endif

	printf("\n\n##### COMPILER STARTED #####\n\n");
    initIRcodeFile();
    initMipsFile();
	
	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}
	yyparse();
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}