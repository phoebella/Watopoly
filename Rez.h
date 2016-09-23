#ifndef _REZ_H_
#define _REZ_H_
#include "Nonacademic.h"

class Rez : public Nonacademic {
public:
    Rez(std::string name,int row, int col, bool ownable, int square_num, int purchase_cost, std::string monopoly, int rent, std::shared_ptr<Player> owner);
    void set_rent(int i = 0)override;
    ~Rez();
};


#endif

