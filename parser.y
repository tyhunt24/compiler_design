%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

VarDecl:    TYPE ID SEMICOLON {printf("\n RECOGNIZED RULE: VARIABLE DECLERATION");
                                //Create a Symbol Table
                                //search to see if it is already in there
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
    |   Expr BinOp Expr {printf("\nRECONGINZED RULE: Addition statement");
                            // todo put this in the abstract syntax tree

                            // todo Do Semantic Checks to make sure Expr equals Expr
                        }
    |   ID EQ Expr {printf("\nRECONGINZED RULE: Assignment statement");
                    // todo send this to the abstract syntax tree

                    // todo Semantic Checks to make the right side equals the left side 
                    }
    |   WRITE Expr {printf("\nRECONGIZED RULE: Print Statement");
                    //todo put this in the abstract syntax tree
                    }
;

Primary: ID {printf("\n ID"); 
                // ? Do I need to do something with all of these things below here
            }
    | NUMBER {printf("\n Number");
                // ? What do I need to do with these two parts? and below as wel
            }
;

BinOp:  OP {printf("Plus Operator");}
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