#include "etc.hpp"

//Return
Return::Return(baseAST* expression) {
    returnExpr = expression;
}
void Return::updateContext(variableContext &funcVariables, variableTypeRegContext &funcVariableTypes) {
    returnExpr->updateContext(funcVariables, funcVariableTypes);
}