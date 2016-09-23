#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Gameboard.h"
#include "Player.h"
#include "Textdisplay.h"
#include "Academic.h"
#include "Square.h"
#include "Ownable.h"

using namespace std;
const int standard_roll = 4;

Gameboard::Gameboard(int num_players, int num_rolls, vector<shared_ptr<Player>>players, shared_ptr<Player> cur_player, vector<shared_ptr<Square>>squares, shared_ptr<Textdisplay> text):num_players{num_players}, num_rolls{num_rolls}, players{players}, cur_player{cur_player}, squares{squares}, text{text}{
}

void Gameboard::set_cur_player(shared_ptr<Player> p){
    cur_player = p;
}

char Gameboard::get_cur_player(){
    return cur_player->get_char();
}

void Gameboard::return_to_market(shared_ptr<Ownable> s){
    if(s->get_cur_improvement()>0){
        shared_ptr<Academic> ptr = dynamic_pointer_cast<Academic>(s);
        int sum = s->get_cur_improvement();
        ptr->change_improvement(-sum);
    }
}

void Gameboard::trade(shared_ptr<Player> a,shared_ptr<Player> b, int money, string c){    //a sell, b buy
    shared_ptr<Ownable> tmp = a->building_in_list(c);
    a->sell_building(tmp,money);
    b->buy_building(tmp,money);
}

void Gameboard::trade(shared_ptr<Player> a,shared_ptr<Player> b, string c, string d){ //a sell c to b, b sell d to a
    shared_ptr<Ownable> tmp1 = a->building_in_list(c);
    shared_ptr<Ownable> tmp2 = b->building_in_list(d);
    a->sell_building(tmp1,0);
    b->buy_building(tmp1,0);
    b->sell_building(tmp2,0);
    a->buy_building(tmp2,0);
}

bool Gameboard::can_get_roll(){
    if((num_rolls>0)&&(num_rolls<=standard_roll))return true;
    return false;
}

int Gameboard::get_cur_roll(){
    return num_rolls;
}

void Gameboard::set_num_roll(int i){
    num_rolls+=i;
}

shared_ptr<Textdisplay> Gameboard::get_text(){
    return text;
}


bool Gameboard::kick_out(shared_ptr<Player> p){
    int num = players.size();
    if(num-1<=1)return true;
    for(int i = 0; i< players.size();++i){
        if(players[i]->get_next_player()==p){
            players[i]->set_next_player(p->get_next_player());
        }
        int trace = 0;
        for(;trace < players.size();++trace){
            if(players[i]==p){
                break;
            }
        }
        players.erase(players.begin()+trace);
    }
    return false;
}


    
    
    
    
    
    
    
    
    
    
    




