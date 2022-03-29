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
//Forward decl
forwardDeclaration::forwardDeclaration(std::string identifier) {
    funName = identifier;
}

void forwardDeclaration::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const {

}


//Functions
//Function with no code ie int f();
Function::Function(std::string returnType, std::string name, int funcNum) {
    hasStatements = false;
    hasParams = false;
    std::cout << name << std::endl;
    FuncName = name;
}
//Function with no parameter list
Function::Function(std::string returnType, std::string name, baseAST* multiStatements, int funcNum) {
    hasStatements = true;
    hasParams = false;
    exitFuncLabel = ":EXITFUNC_" + std::to_string(funcNum);
    std::cout << name << std::endl;
    node = function_e;
    statementList = multiStatements;
    FuncName = name;
}
//Function with parameters
Function::Function(std::string returnType, std::string name, baseAST* multiStatements, baseAST* parameterList, int funcNum) {
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
    //nodeVariables should now contain a list of params
    if(hasParams == true) {
        paramList->updateContext(nodeVariables, nodeVariableTypes, variableRegisters); //<- Update the arguments of the function
        for(int i = 0; i < nodeVariables.size(); i++) {
            //Record where parameters are in the stack
            nodeVariables[i][1] = std::to_string(-((i*4)+4));
        }
    }
    std::cout << "Function now has: " << nodeVariables.size() << " params.\n";
    //Number of params so far
    int paramNum = nodeVariables.size();
    //Add variables into function context
    if(hasStatements == true) {
        statementList->updateContext(nodeVariables, nodeVariableTypes, variableRegisters);
        //nodeVariables should now contain a list of params followed local vars
        //Add context from parameters into function context
        //Allocate into stack
        for(int i = paramNum; i < nodeVariables.size(); i++) {
            nodeVariables[i][1] = std::to_string(-((i*4)+4));
        }
    }
    for(int i = 0; i < nodeVariables.size(); i++) {
        std::cout << "Variable " << nodeVariables[i][0] << " stored at " << nodeVariables[i][1] << "($fp)" << std::endl;
    }
    std::cout << "Function now has: " << nodeVariables.size() << " variables and parameters.\n";
}

void Function::generateCode(std::ofstream &outputFile) const { //doesn't support params yet
    outputFile << ".globl " << FuncName << std::endl;
    outputFile<<FuncName<<":"<<std::endl;
    //Allocate space on stack frame
    outputFile<<"addiu $sp,$sp,-" << (8+(nodeVariables.size()*4))<<std::endl;
    outputFile<<"sw $fp," << (4+(nodeVariables.size()*4)) << "($sp)"<<std::endl; //Stores return address at the bottom of the stack
    outputFile<<"sw $31," << (nodeVariables.size()*4) << "($sp)"<<std::endl; //Stores frame pointer on return (at bottom)
    outputFile<<"addiu $fp,$sp," << (nodeVariables.size()*4) << std::endl;//sets new frame pointer 
    std::cout<<"Function: "<<FuncName<<"\n";
    std::string destReg = "$2";
    //Load params into stack
    if(hasParams == true) {
        paramList->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, destReg);
    }
    //Execute codebody
    if(hasStatements == true) {
        statementList->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, destReg);
    }
    //Loads everything from stack, back to memory for each function
    outputFile<<"nop"<<std::endl;
    outputFile<<"move $sp,$fp"<<std::endl;
    outputFile<<"lw $fp,4($sp)"<<std::endl; //restore old frame
    outputFile<<"lw $31,0($sp)"<<std::endl; //return addr
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

void FuncParamList::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const {
    //Laod params onto stack
    for(int i = 0; (i < nodeVariables.size() && i < 4); i++) {
        outputFile << "sw $" << (i+4) << "," << -((i*4)+4) << "($fp)" << std::endl; 
    }
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