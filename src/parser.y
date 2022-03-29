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

%token T_NUMVAL T_INT T_RETURN T_IDENTIFIER T_WHILE T_IF T_ELSE T_FOR T_INCREMENT
%token T_EQUIVALENCE T_LEQ T_GEQ T_BAND T_BOR T_BXOR T_LAND T_LOR

%type <ASTnode> program multiFunction defFunction funcParamList funcParam codeBody forwardDecl
%type <ASTnode> statement keyword expression declaration funcCall operation term unary
%type <ASTnode> loop if argList comparison incrementation multdiv
%type <string> dataType T_IDENTIFIER 
%type <integer> T_NUMVAL  


%start program

%%
//Main root
program         : multiFunction                                                     {programRoot = $1;}
                ;

//All declared functions
multiFunction   : defFunction                                                       {$$ = new allFunctions($1);}
                | multiFunction defFunction                                         {$$->addFunction($2);} //Will add function to the main allFunction node
                ;

//A function definition
defFunction     : dataType T_IDENTIFIER '(' ')' '{' codeBody '}'                    {$$ = new Function(*$1, *$2, $6, funcCount++);} //Function without params
                | dataType T_IDENTIFIER '(' funcParamList ')' '{' codeBody '}'      {$$ = new Function(*$1, *$2, $7, $4, funcCount++);} //Function with params
                | forwardDecl                                                       {$$ = $1;}
                ;

//Forward decleration
forwardDecl     : dataType T_IDENTIFIER '(' ')' ';'                                 {$$ = new forwardDeclaration(*$2);}
                | dataType T_IDENTIFIER '(' funcParamList ')' ';'                   {$$ = new forwardDeclaration(*$2);}
                ;

//Function parameters
funcParamList   : funcParam                                                         {$$ = new FuncParamList($1);} //Add first func parameter
                | funcParamList ',' funcParam                                       {$$->addParameter($3);}   //Add more func parameters
                ;

funcParam       : dataType T_IDENTIFIER                                             {$$ = new Parameter(*$1, *$2, 0);} //Add parameter values
                | dataType '*' T_IDENTIFIER                                         {$$ = new Parameter(*$1, *$3, 1);} //Add pointer parameter
                ;

//Several lines of code
codeBody        : statement                                                         {$$ = new codeBody($1);} //One line of code in between braces
                | codeBody statement                                                {$$->addStatement($2);} //Mulitple lines of code in between braces
                ;

statement       : declaration                                                       {$$ = $1;} //Declering a variable
                | if                                                                {$$ = $1;}
                | T_IDENTIFIER '=' expression ';'                                   {$$ = new Assign(*$1, $3);} //Assigning to a variable
                | keyword                                                           {$$ = $1;} //A keyword stateword ie return
                | loop                                                              {$$ = $1;}
                ;

//If statement
if              : T_IF '(' expression ')' '{' codeBody '}'                          {$$ = new If(labelCount++, $3, $6);}
                | T_IF '(' expression ')' '{' codeBody '}' T_ELSE '{' codeBody '}'  {$$ = new If(labelCount++, $3, $6, $10);}
                ;

//Loops
loop            : T_WHILE '(' expression ')' '{' codeBody '}'                       {$$ = new While(labelCount++, $3, $6);}
                | T_WHILE '(' expression ')'                                        {$$ = new While(labelCount++, $3);}
                | T_WHILE '(' expression ')' '{' '}'                                {$$ = new While(labelCount++, $3);}
                | T_FOR '(' declaration ';' comparison ';' incrementation ')' '{' codeBody '}'    {$$ = new For(labelCount++, $3, $5, $7, $10);}  
                ;

//Variable declaration
declaration     : dataType T_IDENTIFIER ';'                                         {$$ = new varDeclare(*$2);}
                | dataType T_IDENTIFIER '=' expression ';'                          {$$ = new varDeclare(*$2, new Assign(*$2, $4));}
                ;

dataType        : T_INT                                                             {$$ = new std::string("int");}

//Keywords
keyword         : T_RETURN expression ';'                                           {$$ = new Return($2);}

//Expressions
expression      : expression T_BAND bitwiseOR                                       {}
                | bitwiseOR                                                         {$$ = $1;}
                ;
                
//Bitwise operators (forcing precedence)
bitwiseOR       : expression T_BOR bitwiseAND                                       {}
                | bitwiseAND                                                        {$$ = $1;}
                ;

bitwiseAND      : expression T_BXOR bitwiseXOR                                      {}
                | bitwiseXOR                                                        {$$ = $1;}
                ;

bitwiseXOR      : expression T_LAND logicalAND                                      {}           
                | logicalAND                                                        {$$ = $1;}
                ;

logicalAND      : expression T_LOR logicalOR                                        {}
                | logicalOR                                                         {$$ = $1;}
                ;

logicalOR       : term                                                              {$$ = $1;} 
                | incrementation                                                    {$$ = $1;}
                | operation                                                         {$$ = $1;}
                | comparison                                                        {$$ = $1;}
                ;

//A function call
funcCall        : T_IDENTIFIER '(' ')'                                              {$$ = new functionCall(*$1);}
                | T_IDENTIFIER '(' argList ')'                                      {$$ = new functionCall(*$1, $3);}
                ; 

argList         : expression                                                        {$$ = new funcCallArgs($1);}                                      
                | argList ',' expression                                            {$$->addArg($3);}                           
                ;

//Variable incrementation
incrementation  : T_IDENTIFIER T_INCREMENT                                          {$$ = new increment(*$1);}


//All arithmetic operations
operation       : operation '+' term                                                {$$ = new addOperator($1, $3);}
                | operation '-' term                                                {$$ = new subOperator($1, $3);}
                | multdiv                                                           {$$ = $1;}                                            
                ;

multdiv         : multdiv '/' term                                                  {$$ = new divOperator($1, $3);}
                | multdiv '*' term                                                  {$$ = new multOperator($1, $3);}
                | term
                ;

comparison      : comparison T_EQUIVALENCE term                                     {$$ = new equivalenceOperator($1, $3,labelCount++);}
                | comparison '>' term                                               {$$ = new greaterThan($1, $3,labelCount++);}
                | comparison '<' term                                               {$$ = new lessThan($1, $3,labelCount++);}
                | comparison T_LEQ term                                             {$$ = new lessThanEqual($1, $3,labelCount++);}
                | comparison T_GEQ term                                             {$$ = new greaterThanEqual($1, $3,labelCount++);}
                | term                                                              {$$ = $1;}
                ;

//Variables and constants
term            : funcCall                                                          {$$ = $1;}
                | T_NUMVAL                                                          {$$ = new NUMVAL($1);}   
                | T_IDENTIFIER                                                      {$$ = new Variable(*$1);}
                | '(' expression ')'                                                {$$ = $2;}
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
int funcCount = 0;