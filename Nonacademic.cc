#include "Nonacademic.h"
#include <string>
using namespace std;

Nonacademic::Nonacademic(string name, int row, int col, bool ownable, int square_num, int purchase_cost, string monopoly, int rent, shared_ptr<Player> owner): Ownable{name, row,col,ownable, square_num, purchase_cost,monopoly, rent, owner}{}

Nonacademic::~Nonacademic() {}

int Nonacademic::num_monopoly(){
    int sum = 0;
    string owner = get_owner();
    for(int i = 0; i< monopoly_list.size();++i){
        if(monopoly_list[i]->get_owner()==owner){
            ++sum;
        }
    }
    return sum;
}

