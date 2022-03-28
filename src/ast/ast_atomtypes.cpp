#include "etc.hpp"

        
NUMVAL::NUMVAL(int value) {
    value = value;
}

void NUMVAL::updateContext() {

}

void NUMVAL::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout<<"Number \n";
    outputFile<<"li "<<destReg<<","<<value<<std::endl;
}