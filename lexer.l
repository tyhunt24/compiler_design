%option noyywrap

%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()
#include "parser.tab.h"

int words = 0;
int chars = 0;
int lines = 0;
int errors = 0;

%}

letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
NUMBER      {digit}+(\.{digit}+)?(E[+\-]?(digit)+)?

%%
"/*"    				{
							int c;
							while((c = input()) != 0) {
								if(c == '*') {
									if((c = input()) == '/')
										break;
									else
										unput(c);
								}
							}
						}

"int"|"char"|"float"|"void"	{words++; chars += strlen(yytext); 
		 printf("%s : TYPE\n", yytext);
         yylval.string = strdup(yytext);
         return TYPE;
		}

"write"	{words++; 
		 chars += strlen(yytext);
		 printf("%s : KEYWORD\n", yytext);
         yylval.string = strdup(yytext);
         return WRITE;
		}

"return" {words++; 
		 chars += strlen(yytext);
		 printf("%s : KEYWORD\n", yytext);
         yylval.string = strdup(yytext);
         return RETURN;
		}

{ID}	{words++; chars += strlen(yytext);
		 printf("%s : IDENTIFIER\n",yytext);
         yylval.string = strdup(yytext);
         return ID;
        }

{NUMBER}	{words++; chars += strlen(yytext);
			  printf("%s : NUMBER\n",yytext);
              yylval.number = atoi(strdup(yytext));
              return NUMBER;
			}

";"		{chars++;
		 printf("%s : SEMICOLON \n", yytext);
         yylval.string = strdup(yytext);
         return SEMICOLON;
		}

","		{chars++;
		 printf("%s : COMMA \n", yytext);
         yylval.string = strdup(yytext);
         return COMMA;
		}

"="		{chars++;
		 printf("%s : EQ\n", yytext);
         yylval.string = strdup(yytext);
         return EQ;
		}

"("		{chars++;
		 printf("%s : Left Paren\n", yytext);
         yylval.string = strdup(yytext);
         return OPAREN;
		}

")"		{chars++;
		 printf("%s : Right Paren\n", yytext);
         yylval.string = strdup(yytext);
         return CPAREN;
		}

"["		{chars++;
		 printf("%s : Open Bracket\n", yytext);
         yylval.string = strdup(yytext);
         return OBRACK;
		}

"]"		{chars++;
		 printf("%s : Close Bracket\n", yytext);
         yylval.string = strdup(yytext);
         return CBRACK;
		}

"{"		{chars++;
		 printf("%s : Open Curly Brace\n", yytext);
         yylval.string = strdup(yytext);
         return OCBRACE;
		}

"}"		{chars++;
		 printf("%s : Close Curly Brace\n", yytext);
         yylval.string = strdup(yytext);
         return CCBRACE;
		}

"+" {chars++;
     printf("%s : OPERATOR\n", yytext);
     yylval.string = strdup(yytext);
     return PLUS;
    }

"-" {chars++;
     printf("%s : OPERATOR\n", yytext);
     yylval.string = strdup(yytext);
     return MINUS;
    }

"*" {chars++;
     printf("%s : OPERATOR\n", yytext);
     yylval.string = strdup(yytext);
     return MULTIPLY;
    }

"/" {chars++;
     printf("%s : OPERATOR\n", yytext);
     yylval.string = strdup(yytext);
     return DIVIDE;
    }

[\n]	{lines++; chars=0;}
[ \t]	{chars++;}
.		{chars++;
         printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);
		}
%%
