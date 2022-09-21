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

"int"	{words++; chars += strlen(yytext); 
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

{ID}	{words++; chars += strlen(yytext);
		 printf("%s : IDENTIFIER\n",yytext);
         yylval.string = strdup(yytext);
         return ID;
        }

{NUMBER}	{words++; chars += strlen(yytext);
			  printf("%s : NUMBER\n",yytext);
              yylval.number = atoi(strdup(yytext));
              return NUMBER
			}

";"		{chars++;
		 printf("%s : SEMICOLON \n", yytext);
         yylval.string = strdup(yytext);
         return SEMICOLON;
		}

"="		{chars++;
		 printf("%s : EQ\n", yytext);
         yylval.string = strdup(yytext);
         return EQ;
		}

"+" {chars++;
     printf("%s : OPERATOR\n", yytext);
     yylval.string = strdup(yytext);
     return OPERATOR;
    }

[\n]	{lines++; chars=0;}
[ \t]	{chars++;}
.		{chars++;
         printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);
		}
%%

//Code Section
int main(int argc, char**argv)
{
	#ifdef YYDEBUG
		yydebug = 1;
	#endif

	printf("Compiler started. \n\n");

    //this opens up our test program to run the lexer through
	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}
	yylex();
    
     //prints our total numbers of all of the declared variables from the top
	 printf("Lines: %8d\nWords: %8d\nChars: %8d\nErrors: %7d\n", lines, words, chars, errors);
	 
	 //Certifies sourse code is correct
	 if(errors == 0) {
		printf("The Source code is correct. \n");
	 }
}