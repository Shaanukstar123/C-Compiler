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