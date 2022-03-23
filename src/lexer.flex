%option noyywrap
%{

extern "C" int fileno(FILE *stream);
#include "parser.tab.hpp"
%}

%%

/* INTEGER*/
[0-9]+    {
    yylval.integer = std::stoi(num);
    return T_NUMVAL;}

/* Basic requirements */

[int]			{ return(T_INT); }
[return]		{ return(T_RETURN); }
[if]			{ return(T_IF); }
[else]			{ return(T_ELSE); }
[while]			{ return(T_WHILE); }

/* Intermediate/advanced requirements */
/*

[/*]			{ comment(); }
[auto]			{ return(T_AUTO); }
[break]			{ return(T_BREAK); }
[case]			{ return(T_CASE); }
[char]			{ return(T_CHAR); }
[const]			{ return(T_CONST); }
[continue]		{ return(T_CONTINUE); }
[default]		{ return(T_DEFAULT); }
[do]			{ return(T_DO); }
[double]		{ return(T_DOUBLE); }

[enum]			{ return(T_ENUM); }
[extern]		{ return(T_EXTERN); }
[float]			{ return(T_FLOAT); }
[for]			{ return(T_FOR); }
[goto]			{ return(T_GOTO); }


[long]			{ return(T_LONG); }
[register]		{ return(T_REGISTER); }

[short] 		{ return(T_SHORT); }
[signed]		{ return(T_SIGNED); }
[sizeof]		{ return(T_SIZEOF); }
[static]		{ return(T_STATIC); }
[struct]		{ return(T_STRUCT); }
[switch]		{ return(T_SWITCH); }
[typedef]		{ return(T_TYPEDEF); }
[union]			{ return(T_UNION); }
[unsigned]		{ return(T_UNSIGNED); }
[void]			{ return(T_VOID); }
[volatile]		{ return(T_VOLATILE); }


{L}({L}|{D})*		{ return(check_type()); }

0[xX]{H}+{IS}?		{ return(T_CONSTANT); }
0{D}+{IS}?		{ return(T_CONSTANT); }
{D}+{IS}?		{ return(T_CONSTANT); }
L?'(\\.|[^\\'])+'	{ return(CONSTANT); }





L?\"(\\.|[^\\"])*\"	{ return(STRING_LITERAL); }

"..."			{ return(ELLIPSIS); }
">>="			{ return(RIGHT_ASSIGN); }
"<<="			{ return(LEFT_ASSIGN); }
"+="			{ return(ADD_ASSIGN); }
"-="			{ return(SUB_ASSIGN); }
"*="			{ return(MUL_ASSIGN); }
"/="			{ return(DIV_ASSIGN); }
"%="			{ return(MOD_ASSIGN); }
"&="			{ return(AND_ASSIGN); }
"^="			{ return(XOR_ASSIGN); }
"|="			{ return(OR_ASSIGN); }
">>"			{ return(RIGHT_OP); }
"<<"			{ return(LEFT_OP); }
"++"			{ return(INC_OP); }
"--"			{ return(DEC_OP); }
"->"			{ return(PTR_OP); }
"&&"			{ return(AND_OP); }
"||"			{ return(OR_OP); }
"<="			{ return(LE_OP); }
">="			{ return(GE_OP); }
"=="			{ return(EQ_OP); }
"!="			{ return(NE_OP); }
";"			{ return(';'); }
("{"|"<%")		{ return('{'); }
("}"|"%>")		{ return('}'); }
","			{ return(','); }
":"			{ return(':'); }
"="			{ return('='); }
"("			{ return('('); }
")"			{ return(')'); }
("["|"<:")		{ return('['); }
("]"|":>")		{ return(']'); }
"."			{ return('.'); }
"&"			{ return('&'); }
"!"			{ return('!'); }
"~"			{ return('~'); }
"-"			{ return('-'); }
"+"			{ return('+'); }
"*"			{ return('*'); }
"/"			{ return('/'); }
"%"			{ return('%'); }
"<"			{ return('<'); }
">"			{ return('>'); }
"^"			{ return('^'); }
"|"			{ return('|'); }
"?"			{ return('?'); }

*/
[ \t\v\n\f]		{ ; }
.			{ /* ignore bad characters */ }

%%

void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}