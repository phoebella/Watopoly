#ifndef _CHANCE_H_
#define _CHANCE_H_
#include <string>
#include <map>
#include "Nonownable.h"

class Chance: public Nonownable {
protected:
    std::vector <std::string> s1;
public:
    Chance(std::string name, int row, int col, bool ownable, int square_num);
    virtual std::string calculus(bool open)=0;
};

#endif

