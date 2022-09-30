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
                             //Show that we have access to symbol table
                             int insymTab = found($2, currentScope);
                            
                            //Check to see if the ID is in the symbol table
                            if (insymTab == 0) 
                                addItem($2, "Var", $1, 0, currentScope); //if not in the symbol table add it
                                
                            //if in the symbol table throw a semantic Error
                            else
                                printf("Semantic Error: Var %s is already in the symbol table", $2);
                            
                            // print what the symbol table looks like
                            showSymTable();

                            //place the type in the tree
                            struct AST* type = tree($1, NULL, NULL);
                            struct AST* id = tree($2, NULL, NULL);
                        $$ = tree("Type", type, id);
                             }

;

StmtList: Stmt  
        | Stmt StmtList
;

Stmt: Expr SEMICOLON
;

Expr:   Primary {printf("\nRECOGNIZED RULE: Simpliest Statement\n");}
    |   ID EQ Expr {printf("\nRECONGINZED RULE: Assignment statement\n");
                        
                    }

        |   Expr BinOp Expr {printf("\nRECONGINZED RULE: Addition statement\n");

                        }

                        
    |   WRITE Expr {printf("\nRECONGIZED RULE: Print Statement\n");
                    }
;

Primary: ID {printf("\n ID\n"); 
            }
    | NUMBER {printf("\n Number\n");}

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