%option noyywrap
%{
#define YYDEBUG 1
extern "C" int fileno(FILE *stream);
#include "parser.tab.hpp"
%}

%%

"int"	  	                        {/* Keywords */ return(T_INT); }
"return"		                      { return(T_RETURN);}
"while"                           {return(T_WHILE);}
"if"                              {return(T_IF);}
"else"                            {return(T_ELSE);}
"for"                             {return(T_FOR);}


[_a-zA-Z][0-9_a-zA-Z]*            {/* Variables */
                                    yylval.string = new std::string(yytext); 
                                    return T_IDENTIFIER;}
[0-9]+                            {/* Numbers */
                                    yylval.integer = strtod(yytext, 0);
                                    return T_NUMVAL;}

[ \t\r\n]                         { ; }

.                                 {return yytext[0];}

%%
#include <stdlib.h>

void yyerror (char const* message)
{
  fprintf (stderr, "Flex Error: %s\n", message); /* s is the text that wasn't matched */
  exit(1);
}