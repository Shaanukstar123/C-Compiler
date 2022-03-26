%option noyywrap
%option noinput 
%option nounput
%{

extern "C" int fileno(FILE *stream);
#include "parser.tab.hpp"
%}

%%


[0-9]+    {/* Numbers */ yylval.integer = std::stoi(yytext); return T_NUMVAL;}

[_a-zA-Z][0-9_a-zA-Z]*            {  /* Variables */ std::string *text=new std::string(yytext);  yylval.string=text; return T_IDENTIFIER;}


int		  	  {/* Keywords */ return(T_INT); }
return		  { return(T_RETURN); }

[+]                                {/* operators*/ return yytext[0];}
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}