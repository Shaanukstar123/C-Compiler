#include "etc.hpp"

        
NUMVAL::NUMVAL(int value) {
    value = value;
}

void NUMVAL::updateContext() {

}

void NUMVAL::codeGeneration(std::ofstream &outputFile, const variableContext nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters, std::string destReg){
    outputFile<<"li "<<destReg<<" "<<value;
}