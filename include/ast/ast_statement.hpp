#ifndef ast_statement.hpp
#define ast_statement.hpp

#include "ast.hpp"

class codeBody : public baseAST{
    public:
        std::vector<baseAST*> statementList;
        codeBody(baseAST* firstStatement);
        void addStatement(baseAST* statement);
        void updateContext(variableContext &funcVariables, variableTypeRegContext &funcVariableTypes, variableTypeRegContext &funcVariablesReg) override;
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};


class varDeclare : public baseAST{
    public:
        std::string var;
        baseAST* expression;
        varDeclare(std::string varName);
        varDeclare(std::string varName, baseAST* expression);
        void updateContext(variableContext &funcVariables, variableTypeRegContext &funcVariableTypes, variableTypeRegContext &funcVariablesReg);
};

class Assign : public baseAST {
    public:
        std::string var;
        baseAST* varExpr;
        Assign(std::string varName, baseAST* varExpression);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
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