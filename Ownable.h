#ifndef _OWNABLE_H_
#define _OWNABLE_H_

#include <string>
#include <memory>
#include <vector>
#include "Square.h"

class Player;

class Ownable: public std::enable_shared_from_this <Ownable>, public Square {
protected:
    int purchase_cost;
    std::string monopoly;
    std::vector<std::shared_ptr<Ownable>> monopoly_list;
    int rent;
    std::shared_ptr<Player> owner;
    bool mortgage;
    int current_improvement;
public:
    Ownable(std::string name, int row, int col, bool ownable, int square_num, int purchase_cost, std::string monopoly, int rent, std::shared_ptr<Player> owner);
    virtual ~Ownable()=0;
    std::string get_owner();
    char get_owner_char();
    int get_rent();
    bool can_own();
    void pay_rent(std::shared_ptr<Player> p);
    virtual void set_rent(int i = 0)=0;
    void set_owner(std::shared_ptr<Player> p);
    void change_owner(std::shared_ptr<Player> p);
    bool is_mortgage();
    bool is_monopoly(); //should call set_monopoly
    void change_mortgage();
    int get_purchase_cost();
    std::string get_monopoly();
    int get_cur_improvement();  //get the # of improvement the building have, nonacademic return 0
    bool check_block();   //check all ownable in monopoly if any of them have improvement(one have->true)
    void set_monopoly_list(std::vector<std::shared_ptr<Ownable>> m_l);
    void mortgage_building(std::shared_ptr<Ownable> p);
    void unmortgage_building(std::shared_ptr<Ownable> p);
    void change_rent(int i);
    std::shared_ptr<Player> get_cur_owner();
};


#endif

