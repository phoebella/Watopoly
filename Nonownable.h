#ifndef _NONOWNABLE_H_
#define _NONOWNABLE_H_

#include <vector>
#include "Square.h"

class Nonownable : public Square{
public:
    Nonownable(std::string name, int row, int col, bool ownable, int square_num);
    ~Nonownable();
};


#endif

