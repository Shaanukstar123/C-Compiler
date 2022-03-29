#include "etc.hpp"


//AllFunctions
allFunctions::allFunctions(baseAST* firstFunction) {
        node = allFunctions_e; 
        this->addFunction(firstFunction);
    }
void allFunctions::addFunction(baseAST* newFunction) {
//Add new function to list
        functionList.push_back(newFunction);
    }
//Code generation function
void allFunctions::generateCode(std::ofstream &outputFile) const {
        //Update the context of all functions before starting
        for (int i = 0; i < functionList.size(); i++) {
            functionList[i]->updateContext();
            functionList[i]->generateCode(outputFile);
            // outputFile<<FunctionList->name;

        }
    }

//Functions
//Function with no code ie int f();
Function::Function(std::string returnType, std::string name) {
    hasStatements = false;
    hasParams = false;
    std::cout << name << std::endl;
    FuncName = name;
}
//Function with no parameter list
Function::Function(std::string returnType, std::string name, baseAST* multiStatements) {
    hasStatements = true;
    hasParams = false;
    std::cout << name << std::endl;
    node = function_e;
    statementList = multiStatements;
    FuncName = name;
}
//Function with parameters
Function::Function(std::string returnType, std::string name, baseAST* multiStatements, baseAST* parameterList) {
        std::cout << name << std::endl;
        hasStatements = true;
        hasParams = true;
        statementList = multiStatements;
        //Add context from parameters into function context
        paramList = parameterList;
        //paramList->updateContext(nodeVariables, nodeVariableTypes, variableRegisters); //<- Update the arguments of the function
        std::cout << "Function now has: " << nodeVariables.size() << " parameters.\n";
        FuncName = name;
    }
//Update function context and save them 
void Function::updateContext() {
        //Add variables into function context
        if(hasStatements == true) {
            statementList->updateContext(nodeVariables, nodeVariableTypes, variableRegisters);
            //nodeVariables should now contain a list local vars
            //Add context from parameters into function context
            std::cout << "Function now has: " << nodeVariables.size() << " variables.\n";
            //Allocate into stack
            for(int i = 0; i < nodeVariables.size(); i++) {
                nodeVariables[i][1] = std::to_string((i*4)+8);
            }
        }
        int varNum = nodeVariables.size();
        //nodeVariables should now contain a list local vars followed by params
        if(hasParams == true) {
            paramList->updateContext(nodeVariables, nodeVariableTypes, variableRegisters); //<- Update the arguments of the function
            for(int i = varNum; i < nodeVariables.size(); i++) {
                nodeVariables[i][1] = std::to_string((i*4)+8);
            }
        }
        std::cout << "Function now has: " << nodeVariables.size() << " variables and parameters.\n";

    }

void Function::generateCode(std::ofstream &outputFile) const { //doesn't support params yet
    outputFile << ".globl " << FuncName << std::endl;
    outputFile<<FuncName<<":"<<std::endl;
    outputFile<<"addiu $29,$29,-8"<<std::endl;
    outputFile<<"sw $31,4($29)"<<std::endl; //Stores return address at the bottom of the stack
    outputFile<<"sw $30,0($29)"<<std::endl; //Stores frame pointer on top of it
    outputFile<<"move $30,$29" << std::endl;//stores
    std::cout<<"Function: "<<FuncName<<"\n";
    std::string destReg = "$2";
    statementList->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, destReg);
    //Loads everything from stack, back to memory for each function
    outputFile<<"nop"<<std::endl;
    outputFile<<"move $29,$30"<<std::endl;
    outputFile<<"lw $31,4($29)"<<std::endl;
    outputFile<<"lw $30,0($29)"<<std::endl;
    outputFile<<"addiu $29,$29,"<<nodeVariables.size()+8<<std::endl; //probably wrong
    outputFile<<"j $31"<<std::endl;
    outputFile<<"nop"<<std::endl;
}

//FuncParamList
//This class has all the updated variable context from the single parameters
FuncParamList::FuncParamList(baseAST* firstParam) {
    node = function_e;
    this->addParameter(firstParam);
}
//Add parameters, and modify the node's local context as these are variables
void FuncParamList::addParameter(baseAST* newParam) {
    //Every new parameter is basically a variable
    newParam->updateContext(nodeVariables, nodeVariableTypes, variableRegisters);
}
//Called by function to update its context
void FuncParamList::updateContext(variableContext &functionVars, variableTypeRegContext &functionVarTypes, variableTypeRegContext &varLocations) {
    for(int i = 0; i <= nodeVariables.size()-1; i++) {
        std::cout << i <<"\n";
        functionVars.push_back(nodeVariables[i]);
    }
    if(nodeVariables.size() > 4) {
        std::cout << "Param list larger than 4!\n";
    }
    std::cout << "finished adding " << nodeVariables.size()-1 << " params\n";

}

//Parameter
//Function parameters have variable name and type 
Parameter::Parameter(std::string type, std::string name, int pointer) {
    nodeVariables = {{name, "0"}};
    isPointer = pointer;
    paramtype = type;
    paramname = name;
}
//Passing in parameters creates variables so these must be added to function context
void Parameter::updateContext(variableContext &functionVars, variableTypeRegContext &functionVarTypes, variableTypeRegContext &varLocations) {
    //Add parameter to function context
    std::cout << "adding param " << paramname << std::endl;
    functionVars.push_back(nodeVariables[0]);
}