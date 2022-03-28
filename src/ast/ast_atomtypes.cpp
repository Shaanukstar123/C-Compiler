#include "etc.hpp"

//Terminal leaf containing a number
NUMVAL::NUMVAL(int value) {
    value = value;
}

void NUMVAL::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout<<"Number \n";
    outputFile<<"li "<<destReg<<","<<value<<std::endl;
}

//Terminal containing variable
Variable::Variable(std::string varName) {
        varName = varName;
}

void Variable::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout<<"variable \n";
}
