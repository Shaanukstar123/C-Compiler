#ifndef ast_operators.hpp
#define ast_operators.hpp

#include "ast.hpp"

class baseOP : public baseAST {
    public:
        baseAST* leftChild;
        baseAST* rightChild;
};

class addOperator : public baseAST {
    public:
        baseAST* leftOp;
        baseAST* rightOp;
        addOperator(baseAST* leftChild, baseAST* rightChild);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

#endif