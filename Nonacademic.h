#ifndef _NONACADEMIC_H_
#define _NONACADEMIC_H_
#include <string>
#include <vector>
#include "Ownable.h"

class Player;

class Nonacademic: public Ownable {
public:
    Nonacademic(std::string name, int row, int col, bool ownable, int square_num, int purchase_cost, std::string monopoly, int rent, std::shared_ptr<Player> owner);
    virtual void set_rent(int i = 0)=0;
    virtual ~Nonacademic()=0;
    int num_monopoly();
};


#endif

