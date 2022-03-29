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
    for(int i = 0; i < nodeVariables.size(); i++) {
        if(nodeVariables[i][0].compare(varName) == 0) {
            outputFile << "lw " << destReg << "," << nodeVariables[i][1] << "($fp)" << std::endl;
            break;
        }
    }
}
