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
void allFunctions::codeGeneration(std::ofstream &outputFile) const {
        //Update the context of all functions before starting
        for (int i = 0; i < functionList.size(); i++) {
            functionList[i]->updateContext();
            functionList[i]->codeGeneration(outputFile);
        }
    }


//Functions
//Function with no code ie int f();
Function::Function(std::string returnType, std::string name) {
    std::cout << name << std::endl;
    FuncName = name;
}
//Function with no parameter list
Function::Function(std::string returnType, std::string name, baseAST* multiStatements) {
        std::cout << name << std::endl;
        node = function_e;
        statementList = multiStatements;
        FuncName = name;
    }
//Function with parameters
Function::Function(std::string returnType, std::string name, baseAST* multiStatements, baseAST* paramList) {
        std::cout << name << std::endl;
        baseAST* statementList = multiStatements;
        //Add context from parameters into function context
        paramList->updateContext(paramVars, paramTypes); //<- Update the arguments of the function
    }
//Update function context and save them 
void Function::updateContext() {
        paramList->updateContext(paramVars, paramTypes);
        statementList->updateContext(nodeVariables, nodeVariableTypes);
    }


//FuncParamList
//This class has all the updated variable context from the single parameters
FuncParamList::FuncParamList(baseAST* firstParam) {
        node = function_e;
        this->addParameter(firstParam);
    }
//Add parameters, and modify the node's local context as these are variables
void FuncParamList::addParameter(baseAST* newParam) {
        newParam->updateContext(nodeVariables, nodeVariableTypes);
    }
//Called by function to update its context
void FuncParamList::updateContext(variableContext &functionVars, variableTypeRegContext &functionVarTypes) {
        functionVars.insert(nodeVariables.begin(), nodeVariables.end());
        functionVarTypes.insert(nodeVariableTypes.begin(), nodeVariableTypes.end());
 //Function params do not need to update their context to match the entire function
    }

//Parameter
//Function parameters have variable name and type 
Parameter::Parameter(std::string type, std::string name, int pointer) {
        isPointer = pointer;
        paramtype = type;
        paramname = name;
    }
//Passing in parameters creates variables so these must be added to function context
void Parameter::updateContext(variableContext &functionVars, variableTypeRegContext &functionVarTypes) {
        functionVars.insert(std::make_pair(paramname, NULL));
        functionVarTypes.insert(std::make_pair(paramname, paramtype));
    }