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

%type <program> program allFunctions defFunction funcParamList funcParam codeBody
%type <program> statement keyword expression
%type <string> T_INT
%type <integer> T_NUMVAL


%start program

%%
program : allFunctions                                                              {programRoot = $1;}
        ;

allFunctions    : defFunction                                                       {$$ = new allFunction($1);}
                | allFunctions defFunction                                          {*(allFunction)$$->addFunction($2)} //Will add function to the main allFunction node
                ;

defFunction     : T_TYPE T_IDENTIFIER '(' ')' '{' codeBody '}'                      {$$ = new Function(*$1, *$2, $6);} //Function without params
                | T_TYPE T_IDENTIFIER '(' funcParamList ')' '{' codeBody '}'        {$$ = new Function(*$1, *$2, $7, $4);} //Function with params
                ;

funcParamList   : funcParam                                                         {$$ = new FuncParamList()->addParameter($1);} //Add first func parameter
                | funcParamList ',' funcParam                                       {*(FuncParamList)->addParameter($3);}   //Add more func parameters
                ;

funcParam       : T_TYPE T_IDENTIFIER                                               {$$ = new Parameter(*$1, *$2, False);} //Add parameter values
                | T_TYPE '*' T_IDENTIFIER                                           {$$ = new Parameter(*$1, *$2, True);} //Add pointe parameter
                ;

codeBody        : statement
                | codeBody statement
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