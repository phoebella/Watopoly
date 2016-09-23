#ifndef _HELPER_H_
#define _HELPER_H_

class Player;
bool bank_check(std::shared_ptr<Player> cur_player,std::vector<std::shared_ptr<Player>> players,std::shared_ptr<Gameboard> g);
bool set_player(std::shared_ptr<Player> myplayer,bool ifimprove,std::vector <std::shared_ptr<Player>> players, std::shared_ptr <Gameboard> g);
void host_auction(std::shared_ptr<Ownable> myown, std::shared_ptr<Player> myplayer, std::vector <std::shared_ptr<Player>> players);
void print_turn(std::shared_ptr<Player> q);
void print_before();
void print_after();
void print(bool ifafter);
void  read_cmd(std::shared_ptr<Player> myplayer,std::vector <std::shared_ptr<Player>> players,std::vector <std::string> players_name, std::vector <std::shared_ptr<Square>> squares, std::shared_ptr<Textdisplay>t,std::shared_ptr<Gameboard> g, int n);

#endif

