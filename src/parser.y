%code requires{
    #include "ast.hpp"
 
    //Linking AST to main
    extern const baseAST *programRoot;

  
    int yylex(void);
    void yyerror(const char *);
}

//yyval uses these
%union{
    int integer;
    std::string *string;
    ProgramPtr program;
}
//T_NUM is actual number
//T_INT is int keyword
//T_TYPE are keywords int, float, double, etc
//T_IDENTIFIER IS name of function/variable etc


%token T_NUMVAL T_INT T_RETURN T_TYPE T_IDENTIFIER

%type <program> program allFunctions defFunction funcParamList funcParam multiStatement
%type <program> statement keyword expression
%type <string> T_INT
%type <integer> T_NUMVAL


%start program

%%
program : allFunctions                                                                               {programRoot = $1;}
        ;

allFunctions    : defFunction                                                                        {$$ = new allFunction($1);}
                | allFunctions defFunction                                                           {*(allFunction)$$->addFunction($1)} //Will add function to the main allFunction node
                ;

defFunction     : T_TYPE T_IDENTIFIER '(' ')' '{' multiStatement '}'
                | T_TYPE T_IDENTIFIER '(' funcParamList ')' '{' multiStatement '}'
                ;

funcParamList   : funcParam
                | funcParamList ',' funcParam
                ;

funcParam       : T_TYPE T_IDENTIFIER
                | T_TYPE '*' T_IDENTIFIER
                ;

multiStatement  : statement
                | multiStatement statement
                ;

statement       : keyword
                ;

keyword         : T_RETURN expression ';'
                ;

expression      : T_NUMVAL
                ;

%%

const baseAST *programRoot;

const baseAST* generateAST(FILE *c_source) {
    programRoot = 0;
    yyparse(c_source);
    return programRoot;
}