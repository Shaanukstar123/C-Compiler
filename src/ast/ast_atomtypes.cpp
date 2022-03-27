#include "etc.hpp"

        
NUMVAL::NUMVAL(int value) {
    value = value;
}

void NUMVAL::updateContext() {

}

void NUMVAL::codeGeneration(std::ofstream &outputFile, variableContext &nodeVariables, variableTypeRegContext &nodeVariableTypes, variableTypeRegContext &variableRegisters, std::string destReg) const{
    outputFile<<"li "<<destReg<<" "<<value;
}