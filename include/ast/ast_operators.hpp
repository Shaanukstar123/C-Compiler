#ifndef ast_operators.hpp
#define ast_operators.hpp

#include "ast.hpp"

class baseOP : public baseAST {
    public:
        std::string branchLabel;
        baseAST* leftOp;
        baseAST* rightOp;
};

class addOperator : public baseOP {
    public:
        addOperator(baseAST* leftChild, baseAST* rightChild);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class subOperator : public baseOP {
    public:
        subOperator(baseAST* leftChild, baseAST* rightChild);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class equivalenceOperator : public baseOP {
    public:
        equivalenceOperator(baseAST* leftChild, baseAST* rightChild, int label);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class lessThan : public baseOP {
    public:
        lessThan(baseAST* leftChild, baseAST* rightChild, int label);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class greaterThan : public baseOP {
    public:
        greaterThan(baseAST* leftChild, baseAST* rightChild, int label);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class lessThanEqual : public baseOP {
    public:
        lessThanEqual(baseAST* leftChild, baseAST* rightChild, int label);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class greaterThanEqual : public baseOP {
    public:
        greaterThanEqual(baseAST* leftChild, baseAST* rightChild, int label);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class increment : public baseAST {
    public:
        std::string varRef;
        increment(std::string var);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

#endif