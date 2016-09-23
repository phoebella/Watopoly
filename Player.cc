#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "Player.h"
#include "Textdisplay.h"
#include "Ownable.h"
#include "Academic.h"
using namespace std;

Player::Player(string name, char c_name, int rim, std::vector<std::shared_ptr<Square>> all_squares,int position,shared_ptr<Square> cur_square,shared_ptr<Square> last_square, shared_ptr<Textdisplay> print_text):
name{name}, c_name{c_name}, rim{rim}, all_squares{all_squares}, money{1500}, next_player{nullptr}, position{position}, bankrupt{false}, can_move{true}, cur_square{cur_square}, last_square{last_square}, print_text{print_text}, send{false}, time_single{0}{
    monopoly_name.emplace_back("Arts1");
    monopoly_name.emplace_back("Arts2");
    monopoly_name.emplace_back("Eng");
    monopoly_name.emplace_back("Health");
    monopoly_name.emplace_back("Env");
    monopoly_name.emplace_back("Sci1");
    monopoly_name.emplace_back("Sci2");
    monopoly_name.emplace_back("Math");
}

Player::~Player(){  }

string Player::get_name(){
    return name;
}

char Player::get_char(){
    return c_name;
}

void Player::set_next_player(shared_ptr<Player> q){
    next_player = q;
}


vector<int> Player::give_me_a_num(){
    vector<int> a;
    srand(time(NULL));
    int i = (rand() % 6 + 1);
    a.emplace_back(i);
    i = (rand() % 6 + 1);
    a.emplace_back(i);
    return a;
}


int Player::get_position(){
    return position;
}


void Player::set_position(int square_num, bool sent_to){
    if(sent_to)send=true;
    if(square_num<0){
        square_num += 40;
    }
    if(square_num>=40){
        square_num -= 40;
    }
    last_square = cur_square;
    cur_square = all_squares[square_num];
    /*if(cur_square->get_square_name()=="DC Tims Line"&&sent_to==true){
        
    }*/
    int row_last = last_square->get_row();
    int col_last = last_square->get_col();
    int row_now = cur_square->get_row();
    int col_now = cur_square->get_col();
    notify_square(row_last,col_last,row_now,col_now);

}

void Player::notify_square(int row_last, int col_last, int row_now, int col_now){
    print_text->notified_char(row_last,col_last,row_now,col_now,position,get_char());
}

void Player::notify_improvement(int row, int col){
    print_text->notified_improve(row, col);
}

void Player::unbuild_improvement(int row, int col){
    print_text->cancel_improve(row,col);
}

void Player::change_state(){
    can_move = !can_move;
}

void Player::buy_building(shared_ptr<Ownable> a, int cash){
    money -= cash;
    attach(a);
}

void Player::attach(shared_ptr<Ownable> a){
    //Academic *pa = dynamic_cast<Academic *>(cur_square);
    buildings.emplace_back(a);
    a->change_owner(shared_from_this());
}

void Player::attach(string block){
    monopoly_name.emplace_back(block);
}

void Player::buy_improvement(){
    shared_ptr<Academic> ptr = dynamic_pointer_cast<Academic>(cur_square);
    ptr->set_improvement(1); //change improve_col
    int row = ptr->improve_row();
    int col = ptr->improve_col(); //++ every time build an improvement
    notify_improvement(row,col);
}

void Player::sell_building(shared_ptr<Ownable> a, int m){
    int trace = 0;
    for(;trace < buildings.size();++trace){
        if(buildings[trace]==a){
            break;
        }
    }
    buildings.erase(buildings.begin()+trace);
    money += m;
}

void Player::set_money(int mon){
    money += mon;
}

int Player::get_money(){
    return money;
}

bool Player::is_bankrupt(){
    if(money<0){
        return true;
    } else {
        return false;
    }
}

shared_ptr<Player> Player::get_next_player(){
    return next_player;
}

shared_ptr<Square> Player::get_cur_square(){
    return cur_square;
}


shared_ptr<Ownable> Player::building_in_list(string a){
    for(int i = 0;i<buildings.size();++i){
        if(a==buildings[i]->get_square_name()){
            return buildings[i];
        }
    }
    return nullptr;
}


vector<shared_ptr<Ownable>> Player::my_building(){
    return buildings;
}


void Player::mortgage_building(shared_ptr<Ownable> p){
    p->change_mortgage();
    int mon = p->get_purchase_cost();
    set_money(0.5*mon);
}

void Player::unmortgage_building(shared_ptr<Ownable> p){
    p->change_mortgage();
    int mon = p->get_purchase_cost()*0.6;
    set_money(-mon);
}

void Player::set_rolluprim(int i){
    rim += i;
}

bool Player::have_rolluprim(){
    if(rim>0)return true;
    return false;
}

int Player::tuition(){
    int sum = money;
    for(int i = 0;i<buildings.size();++i){
        sum+=buildings[i]->get_purchase_cost();
        int amount = buildings[i]->get_cur_improvement();
        if(amount>0) {

        shared_ptr<Academic> ptr = dynamic_pointer_cast<Academic>(buildings[i]);
        sum += amount*(ptr->get_improvement_cost());
        }
    }
    return sum/10;
}
       
    

int Player::get_num_roll(){
    return rim;
}

bool Player::send_to(){
    return send;
}

void Player::set_time_single(){
    time_single = 0;
}

bool Player::can_leave_dc(){
    time_single++;
    if(time_single>=3)return true;
    return false;
}

bool Player::can_collect_osap(){
    int cur_num = cur_square->get_square_num();
    int last_num = last_square->get_square_num();
    if(send)return false;
    if(cur_num<last_num){
        return true;
    } else {
        return false;
    }
}

int Player::get_cur_square_num(){
    int num = cur_square->get_square_num();
    return num;
}


void Player::transfer_roll(shared_ptr<Player> p){
    int roll = get_num_roll();
    set_rolluprim(-roll);
    p->set_rolluprim(roll);
}




       
       
       
       
       









