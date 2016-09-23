#ifndef _GYM_H_
#define _GYM_H_
#include "Nonacademic.h"

class Gym : public Nonacademic {
public:
    Gym(std::string name, int row, int col, bool ownable, int square_num, int purchase_cost, std::string monopoly, int rent, std::shared_ptr<Player> owner);
    void set_rent(int i)override;
};


#endif

