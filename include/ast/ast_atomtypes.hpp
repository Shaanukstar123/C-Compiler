#ifndef ast_atomtypes.hpp
#define ast_atomtypes.hpp
#include "ast.hpp"

class NUMVAL : public baseAST {
    public:
        int value;
        NUMVAL(int val);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};

class Variable : public baseAST {
    public:
        std::string varName;
        std::string stackRef;
        Variable(std::string variableName);
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};
#endif