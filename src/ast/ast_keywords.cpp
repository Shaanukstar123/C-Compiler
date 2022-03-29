#include "etc.hpp"

//Return
Return::Return(baseAST* expression) {
    returnExpr = expression;
}
void Return::updateContext(variableContext &functionVars, variableTypeRegContext &functionVarTypes, variableTypeRegContext &varLocations) {
    returnExpr->updateContext(functionVars, functionVarTypes, varLocations);
}

void Return::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout<<"Return \n";
    returnExpr->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,"$2");
    outputFile<<"nop"<<std::endl;
    outputFile<<"move $sp,$fp"<<std::endl;
    outputFile<<"lw $fp,4($sp)"<<std::endl; //restore old frame
    outputFile<<"lw $31,0($sp)"<<std::endl; //return addr
    outputFile<<"j $31"<<std::endl;
    outputFile<<"nop"<<std::endl;
}