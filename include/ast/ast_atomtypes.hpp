#ifndef ast_atomtypes.hpp
#define ast_atomtypes.hpp
#include "ast.hpp"

class NUMVAL : public baseAST {
    int value;
    public:
        NUMVAL(int value);
        void updateContext();
        void codeGeneration(std::ofstream &outputFile) const;
};

#endif