#ifndef ast_keywords.hpp
#define ast_keywords.hpp
#include "ast.hpp"

class Return : public baseAST {
    baseAST* returnExpr;
    public:
        Return(baseAST* expression);
        void updateContext(variableContext const funcVariables, variableTypeRegContext const funcVariableTypes);
        void codeGeneration(std::ofstream &outputFile, const variableContext nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters, std::string regName);
};

#endif