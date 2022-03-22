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
        
        //Function with no parameter list
        Function(std::string returnType, std::string name, baseAST* multiStatements) {
            node = function_e;
            baseAST* statementList = multiStatements;
        }

        //Function with parameters
        //Function(std::string returnType, std::string name, baseAST* multiStatements) {};
};

class FuncParamList : public baseAST{
    //This class has all the updated variable context from the single parameters
    public:
        //Add parameters, and modify the node's local context as these are variables
        void addParameter(baseAST* newParam) {
            newParam->updateContext(nodeVariables, nodeVariableTypes);
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