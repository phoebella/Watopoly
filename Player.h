#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <iostream>
#include <vector>
#include <string>
#include <memory>


class Gameboard;
class Square;
class Ownable;
class Rolluprim;
class Textdisplay;

class Player : public std::enable_shared_from_this<Player> {
protected:
    std::string name;
    char c_name;
    std::vector<std::shared_ptr<Square>> all_squares;
    int money;
    std::shared_ptr<Player> next_player;
    int position;         //add steps according to row and col of that square
    std::vector<std::string> monopoly_name;
    std::vector<std::shared_ptr<Ownable>> buildings;  //building i own
    bool bankrupt;
    bool can_move;
    std::shared_ptr<Square> cur_square;
    std::shared_ptr<Square> last_square;
    int rim;
    std::shared_ptr<Textdisplay> print_text;
    bool send;
    int time_single;
public:
    Player(std::string name, char c_name, int rim, std::vector<std::shared_ptr<Square>> all_squares,int position, std::shared_ptr<Square> cur_square, std::shared_ptr<Square> last_square, std::shared_ptr<Textdisplay> print_text );
    ~Player();
    std::string get_name();
    char get_char();
    void set_next_player(std::shared_ptr<Player> q);
    std::vector <int> give_me_a_num();
    int get_position();
    void change_state();    //from can_move to can't move
    //void notify_position();   //tell standing on which square?(forgot the purpose of this fn)
    void notify_square(int row_last, int col_last, int row_now, int col_now);    //change char in square "I stand on you"
    void set_position(int square_num, bool sent_to);    //change stand on which square
    void buy_building(std::shared_ptr<Ownable> a, int cash);  //consider auction
    void attach(std::shared_ptr<Ownable> a);  //should call
    void attach(std::string block);
    void buy_improvement();
    void notify_improvement(int row, int col);   //I build an improvement on you
    void unbuild_improvement(int row, int col);
    void sell_building(std::shared_ptr<Ownable> a, int m);
    void set_money(int mon);   //money + mon or - mon
    int get_money();
    void set_rolluprim(int i);       //increase or decrease, remember to call set_cur_roll in gameboard to increase num_rolls when the card is used
    bool have_rolluprim();        //have or not
    bool is_bankrupt();
    void transfer_roll(std::shared_ptr<Player> p);
    std::shared_ptr<Player> get_next_player();
    std::shared_ptr<Square> get_cur_square();
    std::shared_ptr<Ownable> building_in_list(std::string a);
    std::vector <std::shared_ptr<Ownable>> my_building();
    void mortgage_building(std::shared_ptr<Ownable> p);
    void unmortgage_building(std::shared_ptr<Ownable> p);
    int tuition();
    int get_num_roll();
    bool send_to();               //see if it is sent to DC tims line
    void set_time_single();       //set time_single() back to 0
    bool can_leave_dc();
    bool can_collect_osap();
    int get_cur_square_num();
};


#endif

