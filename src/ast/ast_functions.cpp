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
//Loads everything from stack, back to memory for each function

            outputFile<<"nop"<<std::endl;
            outputFile<<"move $29,$30"<<std::endl;
            outputFile<<"lw $31,4($29)"<<std::endl;
            outputFile<<"lw $30,0($29)"<<std::endl;
            outputFile<<"addiu $29,$29,"<<nodeVariables.size()<<std::endl; //probably wrong
            outputFile<<"j $31"<<std::endl;
            outputFile<<"nop"<<std::endl;

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
        FuncName = name;
    }
//Update function context and save them 
void Function::updateContext() {
        paramList->updateContext(paramVars, paramTypes);
        statementList->updateContext(nodeVariables, nodeVariableTypes);

    }

void Function::generateCode(std::ofstream &outputFile) const  { //doesn't support params yet
    outputFile << ".globl " << FuncName << std::endl;
    outputFile<<FuncName<<":"<<std::endl;
    outputFile<<"addiu $29,$29,-8"<<std::endl;
    outputFile<<"sw $31,4($29)"<<std::endl; //Stores return address at the bottom of the stack
    outputFile<<"sw $30,0($29)"<<std::endl; //Stores frame pointer on top of it
    outputFile<<"move $30,$29" << std::endl;//stores
    std::cout<<"Function: "<<FuncName<<"\n";
    std::string destReg = "$2";
    statementList->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, destReg);

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