#include "etc.hpp"

//Return
Return::Return(baseAST* expression) {
    returnExpr = expression;
}
void Return::updateContext(variableContext &funcVariables, variableTypeRegContext &funcVariableTypes) {
    returnExpr->updateContext(funcVariables, funcVariableTypes);
}

void Return::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout<<"Return \n";
    returnExpr->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,"$2");
}