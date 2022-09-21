%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
//extern int yyparse();

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
Program: DeclList

;

DeclList:   Decl DeclList
    | Decl
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

StmtList:  Stmt StmtList
;

Stmt: Expr SEMICOLON
;

Expr:   Primary {printf("\nRECOGNIZED RULE: Simpliest Statement\n");}
    |   Expr BinOp Expr {printf("\nRECONGINZED RULE: Addition statement");}
    |   ID EQ Expr {printf("\nRECONGINZED RULE: Assignment statement");}
    |   WRITE Expr {printf("\nRECONGIZED RULE: Print Statement");}
;

Primary: ID {printf("\n ID");}
    | NUMBER {printf("\n Number");}
;

BinOp:  OP {prinf("Plus Operator");}
%%

int main(int argc, char**argv)
{
	#ifdef YYDEBUG
		yydebug = 1;
	#endif

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