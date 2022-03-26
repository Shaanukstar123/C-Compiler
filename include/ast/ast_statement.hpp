#ifndef ast_statement.hpp
#define ast_statement.hpp

#include "ast.hpp"

class codeBody : public baseAST{
    public:
        std::vector<baseAST*> statementList;
        codeBody(baseAST* firstStatement);
        void addStatement(baseAST* statement);
        void updateContext(variableContext const funcVariables, variableTypeRegContext const funcVariableTypes, variableTypeRegContext const funcVariablesReg);
        void codeGeneration(std::ofstream &outputFile);
};


class varDeclare : public baseAST{
    public:
        std::string varName;
        baseAST* expression;
        varDeclare(std::string varName);
        varDeclare(std::string varName, baseAST* expression);
        void updateContext(variableContext const funcVariables, variableTypeRegContext const funcVariableTypes, variableTypeRegContext const funcVariablesReg);
};

class Assign : public baseAST {
    public:
        std::string varName;
        baseAST* varExpression;
        Assign(std::string varName, baseAST* varExpression);
        void codeGeneration(std::ofstream &outputFile, const variableContext funcVariables, const variableTypeRegContext funcVariablesTypes, const variableTypeRegContext funcVariablesReg, std::string regName);
};

class functionCall : public baseAST {
    public:
        std::string funcName;
        std::string funcType;
        baseAST* paramList;
        functionCall(std::string funcType, std::string funcName);
        functionCall(std::string funcType, std::string funcName, baseAST* paramList);
};
#endif