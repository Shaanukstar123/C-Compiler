#ifndef ast_functions.hpp
#define ast_functions.hpp
#include "etc.hpp"

class allFunctions : public baseAST {
    public:
        std::vector<baseAST*> functionList;
        allFunctions(baseAST* firstFunction) {  }
        void addFunction(baseAST* newFunction) {  }
};

class Function : public baseAST{
    public:
        variableContext paramVars;
        variableTypeRegContext paramTypes;
        variableTypeRegContext paramReg;
        Function(std::string returnType, std::string name, baseAST* multiStatements) { }
        Function(std::string returnType, std::string name, baseAST* multiStatements, baseAST* paramList) { };
};

class FuncParamList : public baseAST{
    public:
        FuncParamList() { }
        void addParameter(baseAST* newParam) { }
        void updateContext(variableContext &functionVars, variableTypeRegContext &functionVarTypes) { }
};

class Parameter : public baseAST{
    bool isPointer;
    std::string paramtype;
    std::string paramname;
    public:
        Parameter(std::string type, std::string name, bool pointer) { }
        void updateContext(variableContext &functionVars, variableTypeRegContext &functionVarTypes) { }
};


#endif