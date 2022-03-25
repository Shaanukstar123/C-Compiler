%code requires{
    #include "etc.hpp"
 
    //Linking AST to main
    extern const baseAST *programRoot;

  
    int yylex(void);
    void yyerror(const char *);
}

//yyval uses these
%union{
    int integer;
    std::string* string;
    baseAST* ASTnode;
}
//T_NUM is actual number
//T_INT is int keyword
//T_TYPE are keywords int, float, double, etc
//T_IDENTIFIER IS name of function/variable etc


%token T_NUMVAL T_INT T_RETURN T_TYPE T_IDENTIFIER

%type <ASTnode> program allFunctions defFunction funcParamList funcParam codeBody
%type <ASTnode> statement keyword expression decleration
%type <string> T_INT dataType
%type <integer> T_NUMVAL T_IDENTIFIER


%start program

%%
program : allFunctions                                                              {programRoot = $1;}
        ;

allFunctions    : defFunction                                                       {$$ = new allFunction($1);}
                | allFunctions defFunction                                          {*(allFunction)$$->addFunction($2);} //Will add function to the main allFunction node
                ;

defFunction     : dataType T_IDENTIFIER '(' ')' '{' codeBody '}'                    {$$ = new Function(*$1, *$2, $6);} //Function without params
                | dataType T_IDENTIFIER '(' funcParamList ')' '{' codeBody '}'      {$$ = new Function(*$1, *$2, $7, $4);} //Function with params
                ;

funcParamList   : funcParam                                                         {$$ = new FuncParamList()->addParameter($1);} //Add first func parameter
                | funcParamList ',' funcParam                                       {*(FuncParamList)$$->addParameter($3);}   //Add more func parameters
                ;

funcParam       : dataType T_IDENTIFIER                                             {$$ = new Parameter(*$1, *$2, False);} //Add parameter values
                | dataType '*' T_IDENTIFIER                                         {$$ = new Parameter(*$1, *$3, True);} //Add pointer parameter
                ;

codeBody        : statement                                                         {$$ = new codeBody()->addStatement($1);} //One line of code in between braces
                | codeBody statement                                                {*(codeBody)$$->addStatement($2);} //Mulitple lines of code in between braces
                ;

statement       : decleration                                                       {$$ = $1;} //Declering a variable
                | T_IDENTIFIER '=' expression ';'                                   {$$ = new Assign(*$1, $3);} //Assigning to a variable
                | keyword                                                           {$$ = $1;} //A keyword stateword ie return
                ;

decleration     : dataType T_IDENTIFIER ';'                                         {$$ = new decleration(*$2);}
                | dataType T_IDENTIFIER '=' expression ';'                          {$$ = new decleration(*$2, $4);}
                ;

dataType        : T_INT                                                             {$$ = new std::string("int");}
                ;

keyword         : T_RETURN expression ';'                                           {$$ = new Return($2);}
                ;

expression      : T_NUMVAL                                                          {$$ = new NUMVAL($1);}                 
                ;

%%

const baseAST *programRoot;

const baseAST* generateAST(FILE* c_source) {
    programRoot = 0;
    yyparse(c_source);
    return programRoot;
}