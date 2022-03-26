#include "etc.hpp"

//Return
Return::Return(baseAST* expression) {
    returnExpr = expression;
}
void Return::updateContext(variableContext const funcVariables, variableTypeRegContext const funcVariableTypes) {
    returnExpr->updateContext(funcVariables, funcVariableTypes);
}

void Return::codeGeneration(std::ofstream &outputFile, const variableContext nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters, std::string regName){
    returnExpr->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,"$2");
}