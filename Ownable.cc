#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Ownable.h"
#include "Player.h"
using namespace std;


Ownable::Ownable(string name, int row, int col, bool ownable, int square_num, int purchase_cost, string monopoly, int rent, shared_ptr<Player> owner): Square{name,row, col, ownable,square_num}, purchase_cost{purchase_cost}, monopoly{monopoly}, rent{rent}, owner{owner}, mortgage{false}, current_improvement{0} {}

Ownable::~Ownable(){}

string Ownable::get_owner(){
    if(owner==nullptr)return "no owner";
    return owner->get_name();
}

char Ownable::get_owner_char(){
    if(owner==nullptr)return '0';
    return owner->get_char();
}

int Ownable::get_rent(){
    return rent;
}

bool Ownable::can_own(){
    if(owner)return false;
    return true;
}

void Ownable::pay_rent(shared_ptr<Player> p){
        p->set_money(-rent);
        if(owner){
            owner->set_money(rent);
        }
}


bool Ownable::is_monopoly(){
    if(owner==nullptr)return false;
    string cur_owner = get_owner();
    for(int i = 0; i<monopoly_list.size();++i){
        if(monopoly_list[i]->get_owner()=="no owner")return false;
        if(monopoly_list[i]->get_owner()!=cur_owner){
            return false;
        }
    }
    return true;
}

void Ownable::set_owner(shared_ptr<Player> p){
    owner = p;
    owner->attach(shared_from_this());
    if(is_monopoly()){
        p->attach(get_monopoly());
    }
}

void Ownable::change_owner(shared_ptr<Player> p){
    owner = p;
}



bool Ownable::is_mortgage(){
    return mortgage;
}


void Ownable::change_mortgage(){
    mortgage = !mortgage;
}

int Ownable::get_purchase_cost(){
    return purchase_cost;
}


string Ownable::get_monopoly(){
    return monopoly;
}

int Ownable::get_cur_improvement(){
    return current_improvement;
}

bool Ownable::check_block(){
    if(!is_monopoly())return false;
    for(int i = 0; i< monopoly_list.size();++i){
        if(monopoly_list[i]->get_cur_improvement() > 0)return true;
    }
    return false;
}

void Ownable::set_monopoly_list(vector<shared_ptr<Ownable>> m_l){
    monopoly_list = m_l;
}

void Ownable::change_rent(int i){
    rent = i;
}

shared_ptr<Player> Ownable::get_cur_owner(){
    return owner;
}







