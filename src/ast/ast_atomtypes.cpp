#include "etc.hpp"

//Terminal leaf containing a number
NUMVAL::NUMVAL(int val) {
    value = val;
}

void NUMVAL::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout<<"Number \n";
    outputFile<<"li "<<destReg<<","<<value<<std::endl;
}

//Terminal containing variable
Variable::Variable(std::string variableName) {
        varName = variableName;
}

void Variable::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout<<"variable " << varName << std::endl;
}
