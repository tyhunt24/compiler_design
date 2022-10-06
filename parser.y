%{

/*
    Where I am right now: 
        AST Tree and they are doing what I need them to do
            Make sure I have the right functions in the right places
            I need to look at the mathexpression part and construct a correct AST.
        Semantic Actions
             See where else I need to add the semantic actions
        IR Code
            have some of the functons working but they need more work
            I need to figure out how to store the registers
            Need to figure out how we can go from one register to another
            I need to see what else is suppose to go in here
            I need to see how we can get this to print out the correct way.

        Code Optimization
        Code Generation
            Need to figure out how to Put the IR code into Arm language
            Make sure we have an executable
    
    At the bare minumum we need to have an exectuable so that we still can get
    an okay grade.

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

%type <ast> Program DeclList Decl VarDecl StmtList Stmt Expr MathExpr

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

Expr:   MathExpr {printf("\nRECOGNIZED RULE: Primary Statement\n");
                    $$ = $1;

                }
    |   ID EQ ID {printf("\nRECONGINZED RULE: Assignment statement\n");
                    $$ = AST_assignment("=", $1, $3);

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
                        
                        int semanticChecks = 1;
                        // ------------- Semantic Checks ----------------
                        if(found($1, currentScope) == 0) {
                            printf("Error: Variable %s not found", $1);
                            semanticChecks = 0;
                        }
                        char Int[] = "int";

                        if (strcmp(getVariableType($1, currentScope), Int) != 0) {
                            printf("Error: Variable %s not found", $1);
                            semanticChecks = 0;
                        } 

                        //check if the statement is redundant
                            // ! Make sure it does not print as IR code
                        //change number to str


                       updateValue($1, currentScope, str); // Stores the value in the Symbol Table

                            if (semanticChecks == 1) {
                            printf("All Semantic Checks passed\n");

                            //stores this in the IR code
                            emitConstantIntAssignment($1, str, currentScope);

                            //put what our value is into mips
                            loadValueInts($1, currentScope);
                       }
                    }

    | ID EQ MathExpr {printf("\nRecongized Rule: Math Expression\n");
                        //AST Tree: =: head, $1: left, $3: right
                        $$ = idMathexp("=", $1, $3);

                        //update our value after addition is performed
                        updateValue($1, currentScope, $3->nodeType);
                        if($3->isNumber == 1) {
                            printf("%s", $3->nodeType);
                            loadAddition($1, currentScope);

                        }
                }
                        
    |   WRITE ID {printf("\nRECONGIZED RULE: Print Statement\n");
                    $$ = AST_Write("Write", $2, "");
                    emitWriteId($2, currentScope);
                    writeValue($2, currentScope);
                }
;

MathExpr: MathExpr OP MathExpr {printf("\nReconiged Rule: Math Expression\n");
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
                                    $$ = n; // push that subtree so Biso takes care of it.
                                }   
                                    else if($1->isNumber == 1) {
                                        int num1 = atoi($1->nodeType);
                                        char *val1 = getValue($3->nodeType, currentScope);

                                        int num2 = atoi(val1);

                                        int number = num1 + num2; 

                                        char str[50];
                                        sprintf(str, "%d", number);
                                        strcpy($1->nodeType, str);

                                        struct AST *n = newTree($1->nodeType, NULL, NULL);
                                        n->isNumber = 1;
                                        $$ = n; 

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

                                    }

                                    else {
                                        char *val1 = getValue($1->nodeType, currentScope);
                                        char *val2 = getValue($3->nodeType, currentScope);

                                        int num1 = atoi(val1);
                                        int num2 = atoi(val2);
                                        int number = num1 + num2;

                                        char str[50];
                                        sprintf(str, "%d", number);
                                        strcpy($1->nodeType, str);

                                        struct AST *n = newTree($1->nodeType, NULL, NULL);
                                        n->isNumber = 1;
                                        $$ = n; 
                                }
                               
                            }
        | ID {printf("\n ID\n");
            // Checks to make sure the ID is
            if(found($1, currentScope) == 0) {
                printf("SemanticError: %s is not found\n", $1);
            }

            struct AST *n = newTree($1, NULL, NULL);
            $$ = n;
        }

       
    | NUMBER {printf("\n In Number\n");
        char str[50];
        sprintf(str, "%d", $1);
       struct AST * num = newTree(str, NULL, NULL); // put the number into the bottom of the tree

        num->isNumber = 1; // keeps track of when something becomes a number

        $$ = num; //Adds this num back into the tree
    }

;

%%


int main(int argc, char**argv)
{
	// #ifdef YYDEBUG
	// 	yydebug = 1;
	// #endif

	printf("\n\n##### COMPILER STARTED #####\n\n");
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