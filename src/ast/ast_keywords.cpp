#include "etc.hpp"

class Return : public baseAST {
    public:
        baseAST* returnExpr;
        Return(baseAST* expression) {
            returnExpr = expression;
        }
        void updateContext(variableContext const funcVariables, variableTypeRegContext const funcVariableTypes) {
            returnExpr->updateContext(funcVariables, funcVariableTypes);
        }
};