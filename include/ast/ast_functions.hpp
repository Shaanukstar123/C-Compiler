#ifndef ast_functions.hpp
#define ast_functions.hpp
#include "ast.hpp"

class allFunctions : public baseAST {
    public:
        //List of functions
        std::vector<baseAST*> functionList;
        allFunctions(baseAST* firstFunction);
        void addFunction(baseAST* newFunction);
        void generateCode(std::ofstream &outputFile) const override;
};

class Function : public baseAST{
    public:
        variableContext paramVars;
        variableTypeRegContext paramTypes;
        variableTypeRegContext paramReg;
        baseAST* statementList;
        baseAST* paramList;
        std::string FuncName;
        Function(std::string returnType, std::string name);
        Function(std::string returnType, std::string name, baseAST* multiStatements);
        Function(std::string returnType, std::string name, baseAST* multiStatements, baseAST* parameterList);
        void updateContext();
        void generateCode(std::ofstream &outputFile) const;
};

class FuncParamList : public baseAST{
    public:
        FuncParamList(baseAST* firstParam);
        void addParameter(baseAST* newParam);
        void updateContext(variableContext &functionVars, variableTypeRegContext &functionVarTypes, variableTypeRegContext &varLocations) override;
};

class Parameter : public baseAST{
    int isPointer;
    std::string paramtype;
    std::string paramname;
    public:
        Parameter(std::string type, std::string name, int pointer);
        void updateContext(variableContext &functionVars, variableTypeRegContext &functionVarTypes, variableTypeRegContext &varLocations) override;
};



#endif