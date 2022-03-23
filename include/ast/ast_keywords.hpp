#ifndef ast_keywords.hpp
#define ast_keywords.hpp
#include "etc.hpp"

class Return : public baseAST {
    public:
        Return(baseAST* expression) {}
};

#endif