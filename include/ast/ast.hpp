#ifndef ast_hpp
#define ast_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, int> variableContext; //Used to pass variables between nodes in a function
typedef std::map<std::string, std::string> variableTypeRegContext;  //Used to pass variable types

//Enum containing the different node types
enum nodeType {
    allFunctions_e,
    function_e,
    paramlist_e,
    param_e
};

class baseAST {
    protected:
        //Might not be needed but uses an enum to identify what type of node this is
        nodeType node;
        //A map of variable names and their values for functions to retain across all their code
        variableContext nodeVariables;
        //A map of variable names and their types
        variableTypeRegContext nodeVariableTypes;
        //A map of variable names and the registers they will be allocated to
        variableTypeRegContext variableRegisters;
    public:
        virtual void codeGeneration(std::ofstream &outputFile) const;
        virtual void codeGeneration(std::ofstream &outputFile, const variableContext nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters) const;
        virtual void codeGeneration(std::ofstream &outputFile, const variableContext nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters, std::string regName) const;
        virtual void updateContext() const;
        virtual void updateContext(variableContext const nodeVariables, const variableTypeRegContext nodeVariableTypes) const;
        virtual void updateContext(variableContext const nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters) const;
        std::string outputComment(std::string outputComment);
        //Other functions
        void addFunction(baseAST* newFunction);
        void addParameter(baseAST* newParam);
        void addStatement(baseAST* statement);
};

#endif