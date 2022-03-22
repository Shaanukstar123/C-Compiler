#include "etc.hpp"

class allFunctions : public baseAST {
    public:
        //The top level node contains references to all functions and a map containing their contexts  
        //std::map<baseAST*, std::map<variableContext, variableTypeContext>> functionList;
        std::vector<baseAST*> functionList;
        allFunctions(baseAST* firstFunction) {
            node = allFunctions_e; 
            this->addFunction(firstFunction);
        }
        void addFunction(baseAST* newFunction) {
            //Add new function to list
            functionList.push_back(newFunction);
            //functionList[newFunction].insert(std::make_pair(new variableContext, new variableTypeContext));
        }
};

class Function : public baseAST{
    public:
        variableContext paramVars;
        variableTypeContext paramTypes;
        //Function with no parameter list
        Function(std::string returnType, std::string name, baseAST* multiStatements) {
            node = function_e;
            baseAST* statementList = multiStatements;
        }
        //Function with parameters
        Function(std::string returnType, std::string name, baseAST* multiStatements, baseAST* paramList) {
            baseAST* statementList = multiStatements;
            //Add context from parameters into function context
            paramList->updateContext(paramVars, paramTypes); //<- Update the arguments of the function
        };
};

class FuncParamList : public baseAST{
    //This class has all the updated variable context from the single parameters
    public:
        FuncParamList() {
            node = function_e;
        }
        //Add parameters, and modify the node's local context as these are variables
        void addParameter(baseAST* newParam) {
            newParam->updateContext(nodeVariables, nodeVariableTypes);
        }
        //Called by function to update its context
        void updateContext(variableContext &functionVars, variableTypeContext &functionVarTypes) {
            functionVars.insert(nodeVariables.begin(), nodeVariables.end());
            functionVarTypes.insert(nodeVariableTypes.begin(), nodeVariableTypes.end());
            //Function params do not need to update their context to match the entire function
        }
};

class Parameter : public baseAST{
    bool isPointer;
    std::string paramtype;
    std::string paramname;
    //Function parameters have name and type 
    public:
        Parameter(std::string type, std::string name, bool pointer) {
            isPointer = pointer;
            paramtype = type;
            paramname = name;
        }
        //Passing in parameters creates variables so these must be added to function context
        void updateContext(variableContext &functionVars, variableTypeContext &functionVarTypes) {
            functionVars.insert(std::make_pair(paramname, NULL));
            functionVarTypes.insert(std::make_pair(paramname, paramtype));
        }
};