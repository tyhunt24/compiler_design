%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "symbolTable.h"
#include "symtab.h"
#include "AST.h"
#include "IrCode.h"
#include "Assembly.h"

extern int yylex();
extern int yyparse();

extern FILE* yyin;

void yyerror(const char* s);
char currentScope[50] = "global";
char label[50] = "IfStmt";
char otherScope[50];
char returnName[50];

int inreturn = 0;

int is_else = 0;

int in_true = 0;

int in_loop = 0;

char *returnType;

int semanticChecks = 1;

//$$ parses the tree back together
//parser: reads right to left
//find the first argument and second argument in this statement

clock_t t;


/*
  1. Try to get a really simple function running in MIPS. 

 */

%}

%union {
    int number;
    char character;
    char* string;
    struct AST* ast;
}

%token <string> TYPE
%token <string> ID
%token <string> IF
%token <string> ELSE
%token <string> WHILE
%token <char> SEMICOLON
%token <char> COMMA
%token <char> EQ
%token <char> OPAREN
%token <char> CPAREN
%token <char> OBRACK
%token <char> CBRACK
%token <char> OCBRACE
%token <char> CCBRACE
%token <char> PLUS
%token <char> MINUS
%token <char> MULTIPLY
%token <char> DIVIDE
%token <number> NUMBER
%token <string> LT
%token <string> GT
%token <string> GTE
%token <string> LTE
%token <string> EQEQ
%token <string> NOTEQ
%token <string> AND
%token <string> OR
%token WRITE
%token WRITEln
%token RETURN

%printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } NUMBER;

%type <ast> Program DeclList Decl VarDeclList VarDecl FunDecl ParamDecl ParamDecList ParamDecListTail Block CallList StmtList Stmt Expr Math IfExpr WhileStmt RelOps
%left PLUS MINUS
%left MULTIPLY DIVIDE

%start Program

%%
Program: DeclList  {$$ = $1;
                    endMipsFile();
                    t = clock() - t;
                    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
                    printf("Program took %f seconds to execute \n", time_taken);
                    }
        
;

DeclList:   Decl DeclList   {$1->left = $2;
                             $$ = $1;
                            }
    | Decl  { $$ = $1; }
;

Decl: FunDecl
    | VarDeclList
    | StmtList
;

VarDeclList: {$$ = NULL;}
|   VarDecl VarDeclList
;

VarDecl:    TYPE ID SEMICOLON {printf("\n RECOGNIZED RULE: VARIABLE DECLERATION\n");
                                // ----- Semantic Checks ----- //
                                if (found($1, currentScope) == 0) {
                                    
                                    // ----- Symbol Table ----- //
                                    addItem($2, "var", $1, currentScope);
                                }
                                // ----- AST Tree ----- //
                                $$ = AST_assignment("Type", $1, $2);

                                printTable();
                            }
    |       TYPE ID OBRACK NUMBER CBRACK SEMICOLON {printf("\n Array Decleration\n");}

;

FunDecl: TYPE ID OPAREN {
                            // ----- Symbol Table ----- //
                           // addItem($2, "func", $1, currentScope);

                            // copy function name to currentscope
                            strcpy(currentScope, $2);
                            strcpy(label, $2);
                         } 
 ParamDecList CPAREN Block {printf("\nFunction\n");
                            // ----- AST Tree ----- //
                            $$ = ast_func("func", $2, $7);

                            // ----- IR code ----- //
                            labelFunction($2);
                            MipsCreateFunction($2);
                         }
;

ParamDecList: {$$ = NULL;}
    |   ParamDecListTail   
;

ParamDecListTail: ParamDecl
    |   ParamDecl COMMA ParamDecListTail
;

ParamDecl: TYPE ID {printf("\nEncountered Parameter\n");
                        // ----- Symbol Table ----- //
                        addItem($2, "param", $1, currentScope);

                        // ----- AST Actions ----- //
                        $$ = AST_assignment("Type", $1, $2);
                    }

|   TYPE ID OBRACK CBRACK {printf("\nParameter Array\n");}
;


StmtList: Stmt  
        | Stmt StmtList
;

Stmt: Expr SEMICOLON {$$ = $1;}
 | IfExpr {$$ = $1;}
 | WhileStmt {$$ = $1;}
;

Expr:   Math {printf("\nRECOGNIZED RULE: Primary Statement\n");
                    $$ = $1;

                }
    |   ID EQ ID {printf("\nRECONGINZED RULE: Assignment statement\n");
                    // ----- Semantic Checks ----- //
                    if(found($1, currentScope)  == 0) {
                        printf("Semantic Error: %s is not intialized\n", $1);
                        semanticChecks = 0;
                    }

                    if(found($3, currentScope)  == 0) {
                        printf("Semantic Error: %s is not intialized\n", $3);
                        semanticChecks = 0;
                    }

                    // Get Variable Types
                    char *varType1 = getVariableType($1, currentScope);
                    char *varType2 = getVariableType($3, currentScope);

                    // Check Variable Types
                    if(strcmp(varType1, varType2) != 0) {
                        printf("\nSemantic Error: variables Type mistmatch\n");
                        semanticChecks = 0;
                    }

                    // ----- Symbol Table ----- //
                    updateValue($1, currentScope, getValue($3, currentScope));

                    // ----- AST Tree ----- //
                    $$ = AST_assignment("=", $1, $3);

                    // ----- IR code ----- //
                }

    |   ID EQ NUMBER {printf("\n RECONGIZED RULE: Number Decleration\n");
                        // ----- Semantic Checks ----- //
                        if(found($1, currentScope) == 0) {
                            printf("Semantic Error: ID has not been declared");
                        }

                        // ----- Symbol Table ----- //
                        char str[50];
                        sprintf(str, "%d", $3);
                        updateValue($1, currentScope, str);

                        // ----- AST Tree ----- //
                        $$ = AST_assignment("=", $1, str);

                        // ----- IR Code ----- //
                        loadValueInts($1, currentScope, str);

                        }
    
    | ID EQ ID OPAREN CallList CPAREN {printf("\nCall Function: In ID\n");
                                        // ----- Semantic Checks ----- //
                                        if(found($1, currentScope)  == 0) {
                                            printf("Semantic Error: %s is not intialized\n", $1);
                                            semanticChecks = 0;
                                        }

                                        if(found($3, currentScope)  == 0) {
                                            printf("Semantic Error: %s is not intialized\n", $3);
                                            semanticChecks = 0;
                                        }

                                        // Get Variable Types
                                        char *varType1 = getVariableType($1, currentScope);
                                        char *varType2 = getVariableType($3, currentScope);

                                        // Check Variable Types
                                        if(strcmp(varType1, varType2) != 0) {
                                            printf("\nSemantic Error: variables Type mistmatch\n");
                                            semanticChecks = 0;
                                    }

                                      // ----- AST Tree ----- //
                                      // ! Not quite sure what this should look like yet.

                                      // ----- IR Code ----- //
                                      mipsJumpFunction(label);
                        }   

        
    | ID OBRACK Expr CBRACK EQ Expr {printf("\n Recongized Rule: Array Expression\n");}

    | ID EQ Math {printf("\nRecongized Rule: Math Expression\n");
                    // ----- Semantic Checks ----- //
                    if(found($1, currentScope) == 0) {
                        printf("Error: Variable is not found");
                        semanticChecks = 0;
                    }
                    // put the value here
                    if($3->isNumber == 1) {
                        updateValue($1, currentScope, $3->nodeType);

                        printf("\n\n\n\n%s\n\n\n\n", $3->nodeType);
                
                        // ----- IR code ----- //
                      //  loadAddition($1, currentScope);

                    } else {
                        // ----- IR code ----- //
                        printf("Not a number");
                    }

                    // ----- AST Tree ----- //
                    $$ = idMathexp("=", $1, $3);
                
                }

              
    |   WRITE ID {printf("\nRECONGIZED RULE: Print Statement\n");
                    // ----- AST Actions ----- //
                     $$ = AST_Write("Write", $2, "");

                     // ----- IR Code ----- //
                     if (inreturn == 1) {
                     moveFunction($2, currentScope);
                     writeValue($2, currentScope);
                     } else {
                     
                     if(in_true == 1) {
                        jumpExit();
                     }
                     
                     if (in_loop == 1) {
                        writeValueInWhile($2, currentScope);
                     } else {
                        writeValue($2, currentScope);
                     }
                     
                     
                     }


                }
           
            |   WRITEln {printf("\nRECONGIZED RULE: write ln Statement\n");
                    writeNewLine();
                }

    |   RETURN ID {printf("\nFunction Found: Return ID\n");
                    // ----- AST actions ----- //
                    $$ = AST_Write("return", $2, "");

                    // ----- No IR code Here I think
                    strcpy(returnName, $2);
                    strcpy(otherScope, currentScope);

                    inreturn = 1;
                    } 

;

IfExpr: IF OPAREN RelOps CPAREN Block {printf("Entering if statement");
                                        in_true = 1;
                                        // ----- Generate IR Code -----//
                                         // ! Need to Create a label statement here //
                                        MipsCreateLabel(label);

                                        // ----- AST ACTIONS ----- //
                                        $$ = add_tree($1, $3, $5);
}

|   IF OPAREN RelOps CPAREN Block {printf("Entering in First if statement");
                                    in_true = 1;

                                    // --- Create Mips Label --- //
                                     MipsCreateLabel(label);
    } 
    ELSE Block { printf("Entering into an else statement\n");
                        // --- Create Mips Label --- //
                        MipsCreateLabel("ElseStmt");
                        jumpLabel("ElseStmt");

                        // ! --- Create the AST Tree --- //
                        $$ = add_tree($1, $3, $5);
                        $$ = ast_func("else", $7, $8);

}   
;

WhileStmt:  WHILE {strcpy(label, "WhileStmt"); whileMipsCreateLabel(label); in_loop = 1;} OPAREN RelOps CPAREN Block {printf("\nRecongized Rule: While Statement\n");  
                                        // --- Generate IR Code --- //
                                       // jumpLabel(label);

                                        // --- AST Tree --- //
                                        $$ = add_tree($1, $4, $6);
                                        }

;

Block:  OCBRACE VarDeclList StmtList CCBRACE {printf("\nBlock Statement\n");
                                                // ----- AST Actions ----- //
                                                $$ = add_tree("block", $2, $3);

                                                //currentScope -> Global
                                                strcpy(currentScope, "global");                                                
                                            }
;

CallList: {$$ = NULL;}
        | Math {
            // ----- IR Code ----- //
            paramMips($1->nodeType); // Gives us the value in here

            // ----- AST Tree -----//
            $$ = add_tree("Call", $1, NULL);
        }
        | Math COMMA CallList {
           
            // ----- IR Code ----- //
            paramMips($1->nodeType);

            // ----- AST Tree ----- //
            $$ = add_tree("Call", $1, $3);
        }

//Everything below here should be fine.
Math: Math PLUS Math {printf("\nReconiged Rule: Addition Expression\n");
                                
                            //intialize a number to 0
                             int num = 0;

                            //IF $1 and $3 are both numbers
                            if($1->isNumber == 1 && $3->isNumber == 1) {
                                
                                //change from characters to numbers
                                //And Add them
                                int num1 = atoi($1->nodeType);
                                int num3 = atoi($3->nodeType);
                                
                                //add the numbers and add it to first variable
                                int number = num1 + num3;
                                num += number;
                                
                                // ----- AST Tree ----- //
                                char str[50];
                                sprintf(str, "%d", num);
                                $$ = addTree(str, 1);
                            }

                            //If the $1 is a number but the $3 is a variable
                            else if($1->isNumber == 1) {
                                
                                //convert the number from Char to Num
                                //Get the value of the variable from the symbol table
                                //convert it from Char to num
                                int num1 = atoi($1->nodeType);
                                char *val1 = getValue($3->nodeType, currentScope);
                                int num3 = atoi(val1);

                                //add the numbers and add it to first variable
                                int number = num1 + num3;
                                num += number;

                                // ----- AST Tree ----- //
                                char str[50];
                                sprintf(str, "%d", num);
                                $$ = addTree(str, 1);
                            } 

                            //Now $1 is variable and $3 is number
                            else if($3->isNumber == 1) {
                                
                                //do the same as the steps before
                                char *val1 = getValue($1->nodeType, currentScope);
                                int num1 = atoi(val1);
                                int num3 = atoi($3->nodeType);

                                if (in_loop == 1) {
                                    increment($1->nodeType, $3->nodeType, currentScope); // loop through the statement
                                    jumpLabel(label);
                                }
                                    

                                //add the numbers and add it to first variable
                                int number = num1 + num3;
                                num += number;

                                // ----- AST Tree ----- //
                                char str[50];
                                sprintf(str, "%d", num);
                                $$ = addTree(str, 1);
                            }
                            
                            else {
                                    
                                char *val1 = getValue($1->nodeType, currentScope);
                                char *val2 = getValue($3->nodeType, currentScope);

                                if(strcmp(val1, "NULL") != 0 && strcmp(val2, "NULL") != 0) {
                                    
                                    //Gets the numbers from inside of the values
                                    int num1 = atoi(val1);
                                    int num2 = atoi(val2);

                                    int number;
                                    
                                    //add the numbers
                                    number = num1 + num2;
                                    num += number;
                                    char str[50];
                                    sprintf(str, "%d", num);

                                    // ----- AST TREE ----- //
                                    $$ = addTree(str, 1);
                                } else {
                                    mipsInside();

                                    // ---- IR CODE -----//
                                    addMips();

                                    // ----- AST TREE -----//
                                    $$ = add_tree("+", $1, $3);
                                }



                            }
                    }
        | Math MINUS Math {printf("\nReconiged Rule: Subtraction Expression Expression\n");
                            //intialize a number to 0
                            int num = 0;

                            //IF $1 and $3 are both numbers
                            if($1->isNumber && $3->isNumber == 1) {
                                
                                //change from characters to numbers
                                //And Add them
                                int num1 = atoi($1->nodeType);
                                int num3 = atoi($3->nodeType);
                                
                                //add the numbers and add it to first variable
                                int number = num1 - num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            }

                            //If the $1 is a number but the $3 is a variable
                            else if($1->isNumber == 1) {
                                
                                //convert the number from Char to Num
                                //Get the value of the variable from the symbol table
                                //convert it from Char to num
                                int num1 = atoi($1->nodeType);
                                char *val1 = getValue($3->nodeType, currentScope);
                                int num3 = atoi(val1);

                                //add the numbers and add it to first variable
                                int number = num1 - num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            } 

                            //Now $1 is variable and $3 is number
                            else if($3->isNumber == 1) {
                                
                                //do the same as the steps before
                                char *val1 = getValue($1->nodeType, currentScope);
                                int num1 = atoi(val1);
                                int num3 = atoi($3->nodeType);

                                //add the numbers and add it to first variable
                                int number = num1 - num3;
                                num += number;

                                //decrement inside of the loop
                                if (in_loop == 1) {
                                    decrement($1->nodeType, $3->nodeType, currentScope); // loop through the statement
                                    jumpLabel(label);
                                }

                                //printf("%d\n\n\n", num);
                            }

                            //if we are adding both variables and no numbers
                            else { 
                                char *val1 = getValue($1->nodeType, currentScope); 
                                char *val2 = getValue($3->nodeType, currentScope);

                                // check in the Symbol tables are NULL or not.
                                if(strcmp(val1, "NULL") != 0 && strcmp(val2, "NULL") != 0) {
                                
                                    // get the values
                                    int num1 = atoi(val1);
                                    int num2 = atoi(val2);

                                    int number;

                                    number = num1 - num2;
                                    num += number;
                                    char str[50];
                                    sprintf(str, "%d", num);

                                    // ----- AST Tree ----- //
                                    $$ = addTree(str, 1);
                                } else {
                                    mipsInside();
                                    subMips();

                                    // ----- AST Tree ----- //
                                    $$ = add_tree("+", $1, $3);
                                }
                            }

                            }

        | Math MULTIPLY Math {printf("\nReconiged Rule: Addition Expression\n");
                            //intialize a number to 0
                            int num = 0;

                            //IF $1 and $3 are both numbers
                            if($1->isNumber && $3->isNumber == 1) {
                                
                                //change from characters to numbers
                                //And Add them
                                int num1 = atoi($1->nodeType);
                                int num3 = atoi($3->nodeType);
                                
                                //add the numbers and add it to first variable
                                int number = num1 * num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            }

                            //If the $1 is a number but the $3 is a variable
                            else if($1->isNumber == 1) {
                                
                                //convert the number from Char to Num
                                //Get the value of the variable from the symbol table
                                //convert it from Char to num
                                int num1 = atoi($1->nodeType);
                                char *val1 = getValue($3->nodeType, currentScope);
                                int num3 = atoi(val1);

                                //add the numbers and add it to first variable
                                int number = num1 * num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            } 

                            //Now $1 is variable and $3 is number
                            else if($3->isNumber == 1) {
                                
                                //do the same as the steps before
                                char *val1 = getValue($1->nodeType, currentScope);
                                int num1 = atoi(val1);
                                int num3 = atoi($3->nodeType);

                                //add the numbers and add it to first variable
                                int number = num1 * num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            }

                            //if we are adding both variables and no numbers
                            else { 
                                // 
                                char *val1 = getValue($1->nodeType, currentScope); 
                                char *val2 = getValue($3->nodeType, currentScope);

                                if(strcmp(val1, "NULL") != 0 && strcmp(val2, "NULL") != 0) {
                            
                                    int num1 = atoi(val1);
                                    int num2 = atoi(val2);

                                    int number;

                                    number = num1 * num2;
                                    num += number;
                                    char str[50];
                                    sprintf(str, "%d", num);
                                $$ = addTree(str, 1);
                                } else {
                                    mipsInside();
                                    multiMips();
                                    $$ = add_tree("+", $1, $3);
                                }
                            }
                            }

        | Math DIVIDE Math {printf("\nReconiged Rule: Addition Expression\n");
                            //intialize a number to 0
                            int num = 0;

                            //IF $1 and $3 are both numbers
                            if($1->isNumber == 1 && $3->isNumber == 1) {
                                
                                //change from characters to numbers
                                //And Add them
                                int num1 = atoi($1->nodeType);
                                int num3 = atoi($3->nodeType);
                                
                                //add the numbers and add it to first variable
                                int number = num1 / num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            }

                            //If the $1 is a number but the $3 is a variable
                            else if($1->isNumber == 1) {
                                
                                //convert the number from Char to Num
                                //Get the value of the variable from the symbol table
                                //convert it from Char to num
                                int num1 = atoi($1->nodeType);
                                char *val1 = getValue($3->nodeType, currentScope);
                                int num3 = atoi(val1);

                                //add the numbers and add it to first variable
                                int number = num1 / num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            } 

                            //Now $1 is variable and $3 is number
                            else if($3->isNumber == 1) {
                                
                                //do the same as the steps before
                                char *val1 = getValue($1->nodeType, currentScope);
                                int num1 = atoi(val1);
                                int num3 = atoi($3->nodeType);

                                //add the numbers and add it to first variable
                                int number = num1 / num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            }

                            //if we are adding both variables and no numbers
                            else { 
                                char *val1 = getValue($1->nodeType, currentScope); 
                                char *val2 = getValue($3->nodeType, currentScope);

                                if(strcmp(val1, "NULL") != 0 && strcmp(val2, "NULL") != 0) {
                                
                                    int num1 = atoi(val1);
                                    int num2 = atoi(val2);

                                    int number;

                                    number = num1 / num2;
                                    num += number;
                                    char str[50];
                                    sprintf(str, "%d", num);

                                 // ----- AST Tree ----- //
                                $$ = addTree(str, 1);
                                } else {
                                    mipsInside();

                                    // ----- IR Code -----//
                                    divideMips();

                                    // ----- AST Tree ----- //
                                    $$ = add_tree("+", $1, $3);
                                }
                            }
                            }

        | OPAREN Math CPAREN {
            $$ = $2;
        } 
        | ID {printf("\n ID\n");
                printf("\n\n\n\n%s\n\n\n\n", $1);
                $$ = addTree($1, 0);
            }

        | NUMBER {printf("\n In Number\n");
                    char str[50];
                    sprintf(str, "%d", $1);
                    $$ =addTree(str, 1);
                    }

;

//Greater then or Equal too
RelOps: Math GTE Math {printf("\nGreater Than\n");
                        // --- Generate IR code --- //
                        if (in_loop == 1) {
                            bleMips($1->nodeType, $3->nodeType, currentScope, "Exit");
                        } else {
                            bgeMips($1->nodeType, $3->nodeType, currentScope, label);
                        }
                        

                        // --- AST Actions --- //
                        $$ = add_tree($2, $1, $3);
                        }
        
        // Less than or equal to
        | Math LTE Math {printf("\nGreater Than\n");
                        // --- Generate IR code --- //
                        if(in_loop == 1) {
                            bgeMips($1->nodeType, $3->nodeType, currentScope, "Exit");
                        } else {
                              bleMips($1->nodeType, $3->nodeType, currentScope, label);
                        }
                       
                       
                        // --- AST Actions --- //
                        $$ = add_tree($2, $1, $3);
                        }

        // Greater than
        | Math GT Math {printf("\nGreater Than\n");
                        // --- Generate IR code --- //
                        if(in_loop == 1) {
                            bltMips($1->nodeType, currentScope, $3->nodeType, "Exit");
                            printf("\n\n\n\n\n%s\n\n\n\n\n", $1->nodeType);
                            
                        } else {
                            bgtMips($1->nodeType, $3->nodeType, currentScope, label);
                        }
                        
                       
                        // --- AST Actions --- //
                        $$ = add_tree($2, $1, $3);
                        }
            // Less than
        | Math LT Math {printf("\nGreater Than\n");
                        // --- Generate IR code --- //
                        if(in_loop == 1) {
                            bgtMips($1->nodeType, $3->nodeType, currentScope, "Exit");
                            printf("this is what the value is\n\n\n%s\n\n\n\n", $1->nodeType);
                        }else {
                            bltMips($1->nodeType, currentScope, $3->nodeType, label);
                        }


                        // --- AST Actions --- //
                        $$ = add_tree($2, $1, $3);
                        }

          //equal equal
        | Math EQEQ Math {printf("\nGreater Than\n");
                        // --- Generate IR code --- //
                        beqMips($1->nodeType, $3->nodeType, currentScope, label);
                        

                       // --- AST Actions --- //
                       $$ = add_tree($2, $1, $3);
                        }

         // Not equal
        | Math NOTEQ Math {printf("\nGreater Than\n");
                        // --- Generate IR code --- //
                        if(in_loop == 1) {
                            bgtMips($1->nodeType, $3->nodeType, currentScope, "Exit");
                        } else {
                            bneMips($1->nodeType, $3->nodeType, currentScope, label);
                        }
                        


                        // --- AST Actions --- //
                        $$ = add_tree($2, $1, $3);
                        }
;


%%

int main(int argc, char**argv)
{
	// #ifdef YYDEBUG
	// 	yydebug = 1;
	// #endif

    t = clock();


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