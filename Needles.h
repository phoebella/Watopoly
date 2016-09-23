#ifndef _NEEDLUS_H_
#define _NEEDLUS_H_
#include "Chance.h"
#include <memory>
class Player;

class Needles : public Chance{
public:
    Needles(std::string name, int row, int col, bool ownable, int square_num);
    std::string calculus(bool open)override;
    void mutate_money(std::shared_ptr<Player> p, std::string m);
};


#endif

