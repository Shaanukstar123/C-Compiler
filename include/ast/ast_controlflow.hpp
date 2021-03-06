#ifndef ast_controlflow.hpp
#define ast_controlflow.hpp
#include "ast.hpp"

class While : public baseAST {
    public:
        std::string whileLabel;
        std::string endWhileLabel;
        baseAST* expression;
        baseAST* bodyexpr;
        bool has_body;
        While(int label, baseAST* expr);
        While(int label, baseAST* expr, baseAST* body);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};  

class If : public baseAST {
    public:
        std::string ifLabel;
        std::string elseLabel;
        std::string exitLabel;
        baseAST* ifExpr;
        baseAST* trueCond;
        baseAST* falseCond;
        bool hasElse = false;
        If(int label, baseAST* ifExp, baseAST* trueCondition);
        If(int label, baseAST* ifExp, baseAST* trueCondition, baseAST* falseCondition);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class For : public baseAST {
    public:
    std::string label1;
    std::string label2;
    std::string label3;
    baseAST* varDecl;
    baseAST* exitCond;
    baseAST* loopUpdate;
    baseAST* body;
    For(int label, baseAST* var, baseAST* exit, baseAST* update, baseAST* code);
    void updateContext(variableContext &funcVariables, variableTypeRegContext &funcVariableTypes, variableTypeRegContext &funcVariablesReg);
    void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

#endif
