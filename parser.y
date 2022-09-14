%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
%token <char> PlusOp
%token <number> NUMBER
%token WRITE

%printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } NUMBER;

%type <ast> Program DeclList Decl VarDecl StmtList Stmt Expr Primary BinOp

%%

//I am sure that I need to make a lot of changes but I will worry about
//that thursday.
//I need to figure how to do the tree and the Symbol table next
Program: DeclList
;

DeclList: Decl DeclList
    | Decl
;

Decl: VarDecl
    | StmtList
;

VarDecl:    TYPE ID SEMICOLON { printf("First Rule: Variable decleration"); }
;

StmtList: Stmt StmtList
;

Stmt: Expr SEMICOLON
    | WRITE Expr SEMICOLON
;

Expr: Primary {printf("In Primary");}
    | Expr BINOP Expr {printf("Binary Operator");}
    | ID EQ Expr {printf("Primary ID or Number");}
;

Primary: ID {printf("Primary ID");}
    | NUMBER {printf("Primary Number");}
;

BinOp: PlusOp {printf("Plus Sign")}




















%%
