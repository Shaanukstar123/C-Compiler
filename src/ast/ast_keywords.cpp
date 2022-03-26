#include "etc.hpp"

//Return
Return::Return(baseAST* expression) {
    returnExpr = expression;
}
void Return::updateContext(variableContext const funcVariables, variableTypeRegContext const funcVariableTypes) {
    returnExpr->updateContext(funcVariables, funcVariableTypes);
}