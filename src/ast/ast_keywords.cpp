#include "etc.hpp"

class Return : public baseAST {
    public:
        Return(baseAST* expression) {
            baseAST* returnExpr = expression;
        }
};