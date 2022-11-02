%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
char label[50];
char otherScope[50];
char returnName[50];

char *returnType;

int semanticChecks = 1;

//$$ parses the tree back together
//parser: reads right to left
//find the first argument and second argument in this statement


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
%token WRITE
%token RETURN

%printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } NUMBER;

%type <ast> Program DeclList Decl VarDeclList VarDecl FunDecl ParamDecl ParamDecList ParamDecListTail Block CallList StmtList Stmt Expr Math
%left PLUS MINUS
%left MULTIPLY DIVIDE

%start Program

%%
Program: DeclList  {$$ = $1;
                        endMipsFile();
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
                            addItem($2, "func", $1, currentScope);

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

Block:  OCBRACE VarDeclList StmtList CCBRACE {printf("\nBlock Statement\n");
                                                // ----- AST Actions ----- //
                                                $$ = add_tree("block", $2, $3);

                                                //currentScope -> Global
                                                strcpy(currentScope, "global");                                                
                                            }
;

StmtList: Stmt  
        | Stmt StmtList
;

Stmt: Expr SEMICOLON {$$ = $1;}
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
                
                        // ----- IR code ----- //
                        mipsInside();
                        loadAddition($1, currentScope);

                    } else {
                        // ----- IR code ----- //
                    }

                    // ----- AST Tree ----- //
                    $$ = idMathexp("=", $1, $3);
                
                }

              
    |   WRITE ID {printf("\nRECONGIZED RULE: Print Statement\n");
                    // ----- AST Actions ----- //
                     $$ = AST_Write("Write", $2, "");

                     // ----- IR Code ----- //
                     writeValue(returnName, otherScope);

                }

    |   RETURN ID {printf("\nFunction Found: Return ID\n");
                    // ----- AST actions ----- //
                    $$ = AST_Write("return", $2, "");

                    // ----- No IR code Here I think
                    strcpy(returnName, $2);
                    strcpy(otherScope, currentScope);

                    } 
;


CallList: {$$ = NULL;}
        | Math {
            // ----- IR Code ----- //

            // ----- AST Tree -----//
            $$ = add_tree("Call", $1, NULL);
        }
        | Math COMMA CallList {
            // ----- IR Code ----- //

            // ----- AST Tree ----- //
            $$ = add_tree("Call", $1, $3);
        }

//Everything below here should be fine.
Math: Math PLUS Math {printf("\nReconiged Rule: Addition Expression\n");
                                
                                // ----- AST Actions ----- //
                                if($1->isNumber == 1 && $3->isNumber == 1) {
                                int num = 0;
                                int num1 = atoi($1->nodeType);
                                int num3 = atoi($3->nodeType);
                            
                                int number = num1 + num3;
                                num += number;

                            sprintf($1->nodeType, "%d", num);
                            $$ = addTree($1->nodeType, 1);
                            }
                    }
        | Math MINUS Math {printf("\nReconiged Rule: Addition Expression\n");
                            }

        | Math MULTIPLY Math {printf("\nReconiged Rule: Addition Expression\n");
                            }

        | Math DIVIDE Math {printf("\nReconiged Rule: Addition Expression\n");
                            }

        | OPAREN Math CPAREN {
            $$ = $2;
        } 
        | ID {printf("\n ID\n");}

        | NUMBER {printf("\n In Number\n");
                    char str[50];
                    sprintf(str, "%d", $1);
                    $$ =addTree(str, 1);
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