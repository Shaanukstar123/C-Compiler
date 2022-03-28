%code requires{
    #include "etc.hpp"
    //Linking AST to main
    extern const baseAST* programRoot;
    extern FILE* yyin;
  
    int yylex(void);
    void yyerror(const char *);
}
%{
    #define YYDEBUG 1
    %}
%define parse.error verbose
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

%token T_NUMVAL T_INT T_RETURN T_IDENTIFIER T_WHILE

%type <ASTnode> program multiFunction defFunction funcParamList funcParam codeBody
%type <ASTnode> statement keyword expression declaration funcCall operation term unary
%type <ASTnode> loop
%type <string> dataType T_IDENTIFIER 
%type <integer> T_NUMVAL 


%start program

%%
program         : multiFunction                                                     {programRoot = $1;}

multiFunction   : defFunction                                                       {$$ = new allFunctions($1);}
                | multiFunction defFunction                                         {$$->addFunction($2);} //Will add function to the main allFunction node
                ;

defFunction     : dataType T_IDENTIFIER '(' ')' '{' codeBody '}'                    {$$ = new Function(*$1, *$2, $6);} //Function without params
                | dataType T_IDENTIFIER '(' funcParamList ')' '{' codeBody '}'      {$$ = new Function(*$1, *$2, $7, $4);} //Function with params
                ;

funcParamList   : funcParam                                                         {$$ = new FuncParamList($1);} //Add first func parameter
                | funcParamList ',' funcParam                                       {$$->addParameter($3);}   //Add more func parameters
                ;

funcParam       : dataType T_IDENTIFIER                                             {$$ = new Parameter(*$1, *$2, 0);} //Add parameter values
                | dataType '*' T_IDENTIFIER                                         {$$ = new Parameter(*$1, *$3, 1);} //Add pointer parameter
                ;

codeBody        : statement                                                         {$$ = new codeBody($1);} //One line of code in between braces
                | codeBody statement                                                {$$->addStatement($2);} //Mulitple lines of code in between braces
                ;

statement       : declaration                                                       {$$ = $1;} //Declering a variable
                | T_IDENTIFIER '=' expression ';'                                   {$$ = new Assign(*$1, $3);} //Assigning to a variable
                | keyword                                                           {$$ = $1;} //A keyword stateword ie return
                | loop
                ;

loop            : T_WHILE '(' expression ')' '{' codeBody '}'                       {$$ = new While(labelCount++, $3, $6);}
                | T_WHILE '(' expression ')'                                        {$$ = new While(labelCount++, $3);}
                ;

declaration     : dataType T_IDENTIFIER ';'                                         {$$ = new varDeclare(*$2);}
                | dataType T_IDENTIFIER '=' expression ';'                          {$$ = new varDeclare(*$2, $4);}
                ;

dataType        : T_INT                                                             {$$ = new std::string("int");}

keyword         : T_RETURN expression ';'                                           {$$ = new Return($2);}

expression      : T_NUMVAL                                                          {$$ = new NUMVAL($1);} 
                | funcCall                                                          {$$ = $1;}
                | operation
                ;

//A function call
funcCall        : dataType T_IDENTIFIER '(' ')'                                     {$$ = new functionCall(*$1, *$2);}
                | dataType T_IDENTIFIER '(' funcParamList ')'                       {$$ = new functionCall(*$1, *$2, $4);}
                ; 

//All arithmetic operations
operation       : operation '+' term                                                {$$ = new addOperator($1, $3);}
                | term                                                              {$$ = $1;}
                ;

term            : unary                                                             {$$ = $1;}
                | expression                                                        {$$ = $1;}
                ;

unary           : T_NUMVAL                                                          {$$ = new NUMVAL($1);}   
                | T_IDENTIFIER                                                      {$$ = new Variable(*$1);}
                ;


%%

const baseAST* programRoot;

const baseAST* generateAST(std::string c_source) {
    yyin = fopen(c_source.c_str(), "r");
    if(yyin == NULL){
        std::cerr << "Couldn't open input file: " << c_source << std::endl;
        exit(1);
    }
    programRoot = NULL;
    yyparse();
    return programRoot;
}

int labelCount = 0;