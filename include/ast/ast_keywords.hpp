#ifndef ast_keywords.hpp
#define ast_keywords.hpp
#include "ast.hpp"

class Return : public baseAST {
    baseAST* returnExpr;
    public:
        Return(baseAST* expression);
        void updateContext(variableContext &funcVariables, variableTypeRegContext &funcVariableTypes);
        void codeGeneration(std::ofstream &outputFile, variableContext &nodeVariables, variableTypeRegContext &nodeVariableTypes, variableTypeRegContext &variableRegisters, std::string destReg) const;
        
};

#endif