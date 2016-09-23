#ifndef _GAMEBOARD_H
#define _GAMEBOARD_H
#include <string>
#include <vector>
#include <memory>

class Player;
class Square;
class Textdisplay;
class Ownable;



class Gameboard{
    int num_players;
    int num_rolls;
    std::vector<std::shared_ptr<Player>>players;
    std::shared_ptr<Player> cur_player;
    std::vector<std::shared_ptr<Square>>squares;
    std::shared_ptr<Textdisplay> text;
public:
    Gameboard(int num_players, int num_rolls, std::vector<std::shared_ptr<Player>>players, std::shared_ptr<Player> cur_player, std::vector<std::shared_ptr<Square>>squares,std::shared_ptr<Textdisplay> text);
    void set_cur_player(std::shared_ptr<Player> p);
    char get_cur_player();
    void return_to_market(std::shared_ptr<Ownable> s);
    void trade(std::shared_ptr<Player> a,std::shared_ptr<Player> b, int money, std::string c);
    void trade(std::shared_ptr<Player> a,std::shared_ptr<Player> b, std::string c, std::string d);
    int get_cur_roll();
    bool can_get_roll();
    void set_num_roll(int i);
    std::shared_ptr<Textdisplay> get_text();
    bool kick_out(std::shared_ptr<Player> p);
    //void attach_roll(shared_ptr<Rolluprim>, shared_ptr<Player>);
};

#endif

