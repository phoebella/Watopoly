#include <iostream>
#include "Academic.h"
#include "Player.h"
using namespace std;

Academic::Academic(string name, int row, int col,bool ownable, int square_num, int purchase_cost, string monopoly, int rent, shared_ptr<Player> owner, int improvement_row, int improvement_col, const int improvement_cost, int tuition_1, int tuition_2, int tuition_3, int tuition_4, int tuition_5):
Ownable{name, row, col, ownable,square_num,purchase_cost, monopoly, rent, owner},improvement_row{improvement_row}, improvement_col{improvement_col-1}, improvable{true}, standard{5}, improvement_cost{improvement_cost}, tuition_1{tuition_1}, tuition_2{tuition_2}, tuition_3{tuition_3}, tuition_4{tuition_4}, tuition_5{tuition_5}{
    /*cout << "ctor" << improvement_col << endl;
    improvement_col-=5;
     cout << "ctor" << improvement_col << endl;*/
    }


void Academic::set_rent(int i){
    if(current_improvement==0){
        rent =  tuition_1;
    } else if(current_improvement==1){
        rent = tuition_2;
    } else if(current_improvement==2){
        rent = tuition_3;
    } else if(current_improvement==3){
        rent = tuition_4;
    } else if(current_improvement==4){
        rent = tuition_5;
    }
}

int Academic::get_improvement_cost(){
    return improvement_cost;
}

int Academic::improve_row(){
    return improvement_row;
}

int Academic::improve_col(){
    return improvement_col;
}

bool Academic::can_improve(){
    if(!is_monopoly()){
        return false;
    }
    if(is_mortgage()){
        return false;
    }
    if(current_improvement<standard){
        return true;
    } else {
        improvable = false;
        return false;
    }
}

void Academic::set_improvable(){
    improvable = !improvable;
}

void Academic::set_improvement(int i){
    for(int j = 0; j<= i;++j){
        current_improvement += j;
        improvement_col += j;
        if(j>0){
        owner->notify_improvement(improvement_row,improvement_col);
        }
    }
        
}

void Academic::buy_improve(){
    current_improvement += 1;
    improvement_col+=1;
    owner->set_money(-improvement_cost);
    owner->notify_improvement(improvement_row,improvement_col);
    if(current_improvement>=standard) return;
}

void Academic::sell_improve(){
    current_improvement -= 1;
    int half = improvement_cost/2;
    owner->set_money(half);
    owner->unbuild_improvement(improvement_row,improvement_col);
    /*if(current_improvement<=0)*/improvement_col-=1;
}

bool Academic::can_sell_improve(){
    if(is_mortgage())return false;
    if(current_improvement>0){
        return true;
    } else {
        return false;
    }
}

void Academic::change_improvement(int i){
    current_improvement += i;
    improvement_col += i;
}








