#ifndef _ACADEMIC_H_
#define _ACADEMIC_H_
#include "Ownable.h"


class Academic : public Ownable {
    int improvement_row;
    int improvement_col;
    bool improvable;
    const int standard;
    const int improvement_cost;
    int tuition_1;
    int tuition_2;
    int tuition_3;
    int tuition_4;
    int tuition_5;
public:
    Academic(std::string name, int row, int col,bool ownable, int square_num, int purchase_cost, std::string monopoly, int rent, std::shared_ptr<Player> owner, int improvement_row, int improvement_col, const int improvement_cost, int tuition_1, int tuition_2, int tuition_3, int tuition_4, int tuition_5);
    int get_improvement_cost();
    int improve_row();
    int improve_col();
    bool can_improve();
    void set_improvable();
    void set_improvement(int i);  //call set_improvement_cost()
    void set_rent(int i = 0)override;
    void buy_improve();
    void sell_improve();
    bool can_sell_improve();
    void change_improvement(int i);
};

#endif

