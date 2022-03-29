#ifndef ast_operators.hpp
#define ast_operators.hpp

#include "ast.hpp"

//Arithmetic
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

class multOperator : public baseOP {
    public:
        multOperator(baseAST* leftChild, baseAST* rightChild);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class divOperator : public baseOP {
    public:
        divOperator(baseAST* leftChild, baseAST* rightChild);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

//Comparison
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

// LOGICAL OPERATORS

//Logical AND
class logicalAndOperator : public baseOP {
    public:
        logicalAndOperator(baseAST* leftChild, baseAST* rightChild);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

//Logical Or
class logicalOrOperator : public baseOP {
    public:
        logicalOrOperator(baseAST* leftChild, baseAST* rightChild);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class logicalXorOperator : public baseOP {
    public:
        logicalXorOperator(baseAST* leftChild, baseAST* rightChild);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

//BITWISE OPERATORS

class bitwiseAndOperator : public baseOP {
    public:
        bitwiseAndOperator(baseAST* leftChild, baseAST* rightChild);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class bitwiseOrOperator : public baseOP {
    public:
        bitwiseOrOperator(baseAST* leftChild, baseAST* rightChild);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class bitwiseXorOperator : public baseOP {
    public:
        bitwiseXorOperator(baseAST* leftChild, baseAST* rightChild);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

#endif