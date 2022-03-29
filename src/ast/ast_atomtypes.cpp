#include "etc.hpp"

//Terminal leaf containing a number
NUMVAL::NUMVAL(int value) {
    std::cout << "created value\n";
    value = value;
}

void NUMVAL::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout<<"Number \n";
    outputFile<<"li "<<destReg<<","<<value<<std::endl;
}

//Terminal containing variable
Variable::Variable(std::string varName) {
    std::cout << "created variable " << varName << "\n";
        varName = varName;
}

void Variable::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout<<"variable " << varName << std::endl;
}
