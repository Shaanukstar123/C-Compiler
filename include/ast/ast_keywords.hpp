#ifndef ast_keywords.hpp
#define ast_keywords.hpp
#include "ast.hpp"

class Return : public baseAST {
    public:
        baseAST* returnExpr;
        Return(baseAST* expression);
        void updateContext(variableContext &functionVars, variableTypeRegContext &functionVarTypes, variableTypeRegContext &varLocations) override;
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
        
};

#endif