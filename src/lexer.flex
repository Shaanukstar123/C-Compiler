%option noyywrap
%option noinput 
%option nounput
%{

extern "C" int fileno(FILE *stream);
#include "parser.tab.hpp"
%}

%%

[0-9]+    {yylval.integer = std::stoi(yytext); return T_NUMVAL;}

[_a-zA-Z][0-9_a-zA-Z]*            {std::string *text=new std::string(yytext);  yylval.string=text; return T_IDENTIFIER;}

int		  	  { return(T_INT); }
return		  { return(T_RETURN); }

%%

void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}