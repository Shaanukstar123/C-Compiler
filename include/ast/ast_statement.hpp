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
        bool hasExpr; 
        std::string var;
        baseAST* expr;
        varDeclare(std::string variablename);
        varDeclare(std::string variablename, baseAST* expression);
        void updateContext(variableContext &funcVariables, variableTypeRegContext &funcVariableTypes, variableTypeRegContext &funcVariablesReg);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
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
        bool has_args;
        functionCall(std::string funcN);
        functionCall(std::string funcN, baseAST* paramLst);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class funcCallArgs : public baseAST {
    public:
        std::vector<baseAST*> arguments; 
        funcCallArgs(baseAST* firstArg);
        void addArg(baseAST* newArg);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};
#endif