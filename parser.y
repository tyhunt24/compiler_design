%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbolTable.h"
#include "AST.h"

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

%type <ast> Program DeclList Decl VarDecl StmtList Stmt Expr Primary BinOp

%start Program

%%
Program: DeclList   {$$ = $1;}

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
                                //Create a Symbol Table
                                symTabAccess();

                                addItem($2, "Var", $1, 0, currentScope);
                                //search to see if it is already in there

                                // todo Need to check for undelacred variables
                                // todo Need to check if the variable has already been declared
                                showSymTable();
                                //If not found add in there
                                //else: throw an error
                                }

;

StmtList: Stmt  
        | Stmt StmtList
;

Stmt: Expr SEMICOLON
;

Expr:   Primary {printf("\nRECOGNIZED RULE: Simpliest Statement\n");}
    |   Expr BinOp Expr {printf("\nRECONGINZED RULE: Addition statement\n");
                            // todo put this in the abstract syntax tree

                            // todo Need to check for Type Mismatch
                        }
    |   ID EQ Expr {printf("\nRECONGINZED RULE: Assignment statement\n");
                    // todo send this to the abstract syntax tree

                    // todo Semantic Checks to make the right side equals the left side 
                    }
    |   WRITE Expr {printf("\nRECONGIZED RULE: Print Statement\n");
                    //todo put this in the abstract syntax tree
                    }
;

Primary: ID {printf("\n ID\n"); 
                // ? Do I need to do something with all of these things below here
            }
    | NUMBER {printf("\n Number\n");
                // ? What do I need to do with these two parts? and below as wel
            }
;

BinOp:  OP {printf("Plus Operator\n");}
%%


int main(int argc, char**argv)
{
	// #ifdef YYDEBUG
	// 	yydebug = 1;
	// #endif

	printf("\n\n##### COMPILER STARTED #####\n\n");
	
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