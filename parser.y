%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbolTable.h"
#include "AST.h"
//#include "IrCode.h"

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

%type <ast> Program DeclList Decl VarDecl StmtList Stmt Expr Primary

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
                            
                            //--------------- Semantic Checks ------------------
                            if (insymTab == 0) 
                                addItem($2, "Var", $1, 0, currentScope); //if not in the symbol table add it
                                
                            else
                                printf("Semantic Error: Var %s is already in the symbol table", $2);
                            
                            // print what the symbol table looks like
                            showSymTable();

                            $$ = AST_assignment("Type", $1, $2);
                        }
;

StmtList: Stmt  
        | Stmt StmtList
;

Stmt: Expr SEMICOLON
;

Expr:   Primary {printf("\nRECOGNIZED RULE: Primary Statement\n");}
    |   ID EQ ID {printf("\nRECONGINZED RULE: Assignment statement\n");
                    //add this to the symbol table
                    $$ = AST_assignment("=", $1, $3);

                    //------------- Semantic Checks ----------------//
                    int semanticChecks = 1;
                    if(found($1, currentScope) || found($3, currentScope) == 0) {
                        printf("Semantic Error: Variable %s or %s is not initialized\n", $1, $3);
                        semanticChecks = 0;
                    }

                    //checks to make sure they are the correct type
                    if (compareTypes(found($1, currentScope), found($3, currentScope) == 0)) {
                        printf("Semantic Error: Variables %s and %s type mismatch\n", $1, $3);
                        semanticChecks = 0;
                    }

                    if(semanticChecks == 1) {
                        printf("\nAll Semantics Check passed");
                        //emitAssignment($1, $3);  Send IR code to seperate file
                    }
                 }

    |   ID EQ NUMBER {printf("\n RECONGIZED RULE: Number Decleration\n");
                        // ------------- Semantic Checks ----------------
                        if(found($1, currentScope) == 0) {
                            printf("Error: Variable %s not found", $1);
                        }

                        //check if the statement is redundant
                            // ! Make sure it does not print as IR code
                        //change number to str
                        char str[50];
                        sprintf(str, "%d", $3);

                       updateValue($1, currentScope, str); 

                       $$ = AST_assignment("=", $1, str);
                    }               

    |   Expr OP Expr {printf("\nRECONGINZED RULE: Addition statement\n");
                        $$ = newTree("+", $1, $3);

                    }

                        
    |   WRITE Expr {printf("\nRECONGIZED RULE: Print Statement\n");
                    }
;

Primary: ID {printf("\n ID\n"); 
            }
    | NUMBER {printf("\n In Number\n");
    }

;

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