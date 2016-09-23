#ifndef _SLC_H_
#define _SLC_H_
#include <iostream>
#include <string>
#include "Player.h"
#include "Chance.h"
class Player;

class SLC : public Chance {
public:
    SLC(std::string name, int row, int col, bool ownable, int square_num);
    std::string calculus(bool open)override;
    int go_to(std::shared_ptr<Player> p,std::string cal);
};


#endif
























