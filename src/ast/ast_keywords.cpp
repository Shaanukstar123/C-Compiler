#include "etc.hpp"

//Return
Return::Return(baseAST* expression) {
    returnExpr = expression;
}
void Return::updateContext(variableContext &funcVariables, variableTypeRegContext &funcVariableTypes) {
    returnExpr->updateContext(funcVariables, funcVariableTypes);
}

void Return::codeGeneration(std::ofstream &outputFile, variableContext &nodeVariables, variableTypeRegContext &nodeVariableTypes, variableTypeRegContext &variableRegisters, std::string destReg) const{
    outputFile<<"yos";
    returnExpr->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,"$2");

}