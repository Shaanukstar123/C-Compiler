#ifndef ast_controlflow.hpp
#define ast_controlflow.hpp
#include "ast.hpp"

class While : public baseAST {
    public:
        std::string whileLabel;
        std::string endWhileLabel;
        baseAST* expr;
        baseAST* body;
        While(int label, baseAST* expr);
        While(int label, baseAST* expr, baseAST* code);

        void updateContext();
        void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const override;
};  


#endif
