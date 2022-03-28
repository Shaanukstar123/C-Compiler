#ifndef ast_atomtypes.hpp
#define ast_atomtypes.hpp
#include "ast.hpp"

class NUMVAL : public baseAST {
    int value;
    public:
        NUMVAL(int value);
        void updateContext();
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string regName) const override;
};

class Variable : public baseAST {
    std::string varName;
    std::string stackRef;
    public:
        Variable(std::string varName);
        void updateContext();
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string regName) const override;
};
#endif