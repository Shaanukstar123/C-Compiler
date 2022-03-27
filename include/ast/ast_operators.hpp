#ifndef ast_operators.hpp
#define ast_operators.hpp

#include "ast.hpp"

class baseOP : public baseAST {
    public:
        baseAST* leftChild;
        baseAST* rightChild;
};

class addOperator : public baseAST {
    baseAST* leftChild;
    baseAST* rightChild;
    public:
        addOperator(baseAST* leftChild, baseAST* rightChild);
        void codeGeneration(std::ofstream &outputFile, const variableContext nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters, std::string regName);
};

#endif