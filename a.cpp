#include "a.hpp"
#include "gra.hpp"

A::A(Gra* gra) {
    this->gra = *gra;
    for(int x = 0; x < gra->get_size(); x++) {
        for(int y = 0; y < gra->get_size(); y++) {
            this->test[x][y] = gra->get(x, y);
        }
    }
}