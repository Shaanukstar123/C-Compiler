#include "etc.hpp"

class NUMVAL : public baseAST {
    public:
        int value;
        NUMVAL(int value) {
            value = value;
        }

        void codeGen(std::ofstream &outputFile){
            outputFile<<"li "<<"$2,"<<value;
        }
};