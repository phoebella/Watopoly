#include <iostream>
#include <memory>
#include <string>
#include "Rez.h"
#include "Player.h"
using namespace std;

Rez::Rez(std::string name, int row, int col, bool ownable, int square_num, int purchase_cost, string monopoly, int rent, shared_ptr<Player> owner): Nonacademic{name, row,col,ownable, square_num, purchase_cost,monopoly, rent, owner}{}

void Rez::set_rent(int i){
    int num = num_monopoly();
    string cur_own = get_owner();
    if(num==1){
        for(int i= 0;i < monopoly_list.size();++i){
            if(monopoly_list[i]->get_owner()==cur_own){
                monopoly_list[i]->change_rent(25);
            }
        }
    } else if(num==2){
        for(int i= 0;i < monopoly_list.size();++i){
            if(monopoly_list[i]->get_owner()==cur_own){
                monopoly_list[i]->change_rent(50);
            }
        }
    } else if(num==3){
        for(int i= 0;i < monopoly_list.size();++i){
            if(monopoly_list[i]->get_owner()==cur_own){
                monopoly_list[i]->change_rent(100);
            }
        }
    } else if(num==4){
        for(int i= 0;i < monopoly_list.size();++i){
            if(monopoly_list[i]->get_owner()==cur_own){
                monopoly_list[i]->change_rent(200);
            }
        }
    }
}

Rez::~Rez(){}

