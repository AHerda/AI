#ifndef ai_hpp
#define ai_hpp

#include <fstream>
#include "gra.hpp"

class A {
    private:

    Gra gra;
    vector<vector<int>> test;

    public:

    A(Gra* gra);
};

#endif