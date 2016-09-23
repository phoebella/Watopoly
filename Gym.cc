#include <iostream>
#include <memory>
#include <string>
#include "Gym.h"
#include "Player.h"
using namespace std;

Gym::Gym(string name, int row, int col, bool ownable, int square_num, int purchase_cost, string monopoly, int rent, shared_ptr<Player> owner): Nonacademic{name,row,col,ownable, square_num, purchase_cost,monopoly, rent, owner}{}

void Gym::set_rent(int j){
    int num = num_monopoly();
    if(num==1){
        for(int i= 0;i < monopoly_list.size();++i){
            rent = 4*j;
        }
    } else if(num==2){
        for(int i= 0;i < monopoly_list.size();++i){
            rent = 10*j;
        }

    }
}

