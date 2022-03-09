%option noyywrap
%{
#include <stdio.h>
#include "y.tab.h"

void count();
%}

%%

/*Basic requirements*/

[int]			{ count(); return(T_INT); }
[return]		{ count(); return(T_RETURN); }
[if]			{ count(); return(T_IF); }
[else]			{ count(); return(T_ELSE); }
[while]			{ count(); return(T_WHILE); }

/*Intermediate requirements*/

[/*]			{ comment(); }
[auto]			{ count(); return(T_AUTO); }
[break]			{ count(); return(T_BREAK); }
[case]			{ count(); return(T_CASE); }
[char]			{ count(); return(T_CHAR); }
[const]			{ count(); return(T_CONST); }
[continue]		{ count(); return(T_CONTINUE); }
[default]		{ count(); return(T_DEFAULT); }
[do]			{ count(); return(T_DO); }
[double]		{ count(); return(T_DOUBLE); }

[enum]			{ count(); return(T_ENUM); }
[extern]		{ count(); return(T_EXTERN); }
[float]			{ count(); return(T_FLOAT); }
[for]			{ count(); return(T_FOR); }
[goto]			{ count(); return(T_GOTO); }


[long]			{ count(); return(T_LONG); }
[register]		{ count(); return(T_REGISTER); }

[short] 		{ count(); return(T_SHORT); }
[signed]		{ count(); return(T_SIGNED); }
[sizeof]		{ count(); return(T_SIZEOF); }
[static]		{ count(); return(T_STATIC); }
[struct]		{ count(); return(T_STRUCT); }
[switch]		{ count(); return(T_SWITCH); }
[typedef]		{ count(); return(T_TYPEDEF); }
[union]			{ count(); return(T_UNION); }
[unsigned]		{ count(); return(T_UNSIGNED); }
[void]			{ count(); return(T_VOID); }
[volatile]		{ count(); return(T_VOLATILE); }


{L}({L}|{D})*		{ count(); return(check_type()); }

0[xX]{H}+{IS}?		{ count(); return(T_CONSTANT); }
0{D}+{IS}?		{ count(); return(T_CONSTANT); }
{D}+{IS}?		{ count(); return(T_CONSTANT); }
L?'(\\.|[^\\'])+'	{ count(); return(CONSTANT); }

/*INTEGER*/
[0-9]+    {
    std::string num = yytext;
    yylval.numberValue = std::stoi(num);
    return Integer;}

L?\"(\\.|[^\\"])*\"	{ count(); return(STRING_LITERAL); }

"..."			{ count(); return(ELLIPSIS); }
">>="			{ count(); return(RIGHT_ASSIGN); }
"<<="			{ count(); return(LEFT_ASSIGN); }
"+="			{ count(); return(ADD_ASSIGN); }
"-="			{ count(); return(SUB_ASSIGN); }
"*="			{ count(); return(MUL_ASSIGN); }
"/="			{ count(); return(DIV_ASSIGN); }
"%="			{ count(); return(MOD_ASSIGN); }
"&="			{ count(); return(AND_ASSIGN); }
"^="			{ count(); return(XOR_ASSIGN); }
"|="			{ count(); return(OR_ASSIGN); }
">>"			{ count(); return(RIGHT_OP); }
"<<"			{ count(); return(LEFT_OP); }
"++"			{ count(); return(INC_OP); }
"--"			{ count(); return(DEC_OP); }
"->"			{ count(); return(PTR_OP); }
"&&"			{ count(); return(AND_OP); }
"||"			{ count(); return(OR_OP); }
"<="			{ count(); return(LE_OP); }
">="			{ count(); return(GE_OP); }
"=="			{ count(); return(EQ_OP); }
"!="			{ count(); return(NE_OP); }
";"			{ count(); return(';'); }
("{"|"<%")		{ count(); return('{'); }
("}"|"%>")		{ count(); return('}'); }
","			{ count(); return(','); }
":"			{ count(); return(':'); }
"="			{ count(); return('='); }
"("			{ count(); return('('); }
")"			{ count(); return(')'); }
("["|"<:")		{ count(); return('['); }
("]"|":>")		{ count(); return(']'); }
"."			{ count(); return('.'); }
"&"			{ count(); return('&'); }
"!"			{ count(); return('!'); }
"~"			{ count(); return('~'); }
"-"			{ count(); return('-'); }
"+"			{ count(); return('+'); }
"*"			{ count(); return('*'); }
"/"			{ count(); return('/'); }
"%"			{ count(); return('%'); }
"<"			{ count(); return('<'); }
">"			{ count(); return('>'); }
"^"			{ count(); return('^'); }
"|"			{ count(); return('|'); }
"?"			{ count(); return('?'); }

[ \t\v\n\f]		{ count(); }
.			{ /* ignore bad characters */ }

%%

yywrap()
{
	return(1);
}


comment()
{
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0)
		putchar(c);

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0)
		putchar(c1);
}


int column = 0;

void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}
