#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "Player.h"
#include "Square.h"
#include "Academic.h"
#include "Ownable.h"
#include "SLC.h"
#include "Needles.h"
#include "Gameboard.h"
#include "Textdisplay.h"
#include "helper.h"
#include "Gym.h"
using namespace std;
void print_turn(std::shared_ptr<Player> q) {
    cout << "--------------- Player " << q->get_name() << "'s turn ---------------" << endl;
}

void print_before() {
    cout <<"You have the following options: <roll> <asset> <all> <improve> <trade> <mortgage> <unmortgage> <save> <help> <exit>" << endl;
}
void print_after() {
    cout << "You have the following options: <next> <asset> <all> <improve> <trade> <mortgage> <unmortgage> <save> <help> <exit> " << endl;
}

void print(bool ifafter) {
    if(ifafter) {
        cout << "You have the following options: <next> <asset> <all> <improve> <trade> <mortgage> <unmortgage> <save> <help> <exit>" << endl;
    }
    
    if(!ifafter) {
        cout <<"You have the following options: <roll> <asset> <all> <improve> <trade> <mortgage> <unmortgage> <save> <help> <exit>" << endl;
    }
}


void osap(shared_ptr<Player> myplayer) {
    if(myplayer->can_collect_osap()) {
        cout << "Test" <<endl;
        myplayer->set_money(200);
        cout << "You have received $200 from OSAP!" << endl;
    }
    
}



bool bank_check(shared_ptr<Player> myplayer,vector<shared_ptr<Player>> players,shared_ptr<Gameboard> g){
    bool ifend =false;
    if(myplayer->get_money() <0) {
        cout << "You owned bank money, you need to enter bankrupt to declare bankruptcy." <<endl;
        while(true) {
            string b;
            cin >> b;
            if(b=="bankrupt") break;
            cout << "You can only enter bankrupt." << endl;
        }
        vector <shared_ptr<Ownable>> auction_list;
        for(int i =0; i < myplayer->my_building().size();++i) {
            auction_list.emplace_back(myplayer->my_building()[i]);
        }
        int j = auction_list.size()-1;
        while(j>0) {
            g->return_to_market(myplayer->my_building()[j]);
            --j;
        }
        for(int i = 0; i < auction_list.size(); ++i) {
            host_auction(auction_list[i], myplayer, players);
        }
        cout << myplayer->get_name() << "'s proproties has been divided." << endl;
        string left =myplayer->get_name();
        int rim = myplayer->get_num_roll();
        ifend = g->kick_out(myplayer);
        g->set_num_roll(rim);
        cout << left << " has left the game!  Row up the Rim Cup has been destroyed!" << endl;
        
        if(ifend) {
            for(int i = 0; i < players.size(); ++i) {
                if(left!=players[i]->get_name()) {
                    cout << players[i]->get_name() << " is the winner! The game ends!" << endl;
                }
            }
            
            
            
            //     if(ifend) return ifend;
            return true;
        }
    }  return false;
}




bool dc_tims(shared_ptr<Player> myplayer,vector <shared_ptr<Player>> players, bool ifafter, bool ifimprove, vector <shared_ptr<Square>> squares,shared_ptr<Textdisplay>t,shared_ptr <Gameboard> g){
    bool ifroll = true;
    int myposition = myplayer->get_cur_square_num();//////////////////////////////////
    if((myposition==10)&&(myplayer->send_to())) {
        ifroll =false;
        cout << "You are at DC Tims Line, and you cannot leave unless you pay $50, or roll a double. " << endl;
        if(!myplayer->can_leave_dc()) {
            cout << "Would you like to pay?(y/n) " << endl;
            string reply;
            cin >> reply;
            if(reply=="y") {
                myplayer->set_money(-50);
                cout << "You have paid $50, and you can roll again." <<endl;
                ifafter =false;
                ifroll =true;
                print(ifafter);
                
            }
            if(reply!="y") {
                int r1 = myplayer->give_me_a_num()[0];
                int r2 = myplayer->give_me_a_num()[1];
                int cur = myplayer->get_position();
                int r12 = r1 +r2;
                if(r1==r2) {
                    cout << r1<< " + " << r2 << " = " << r1+r2 << "  ";
                    cout << "You rolled a double and left DC Tims." <<endl;
                    ifafter=false;
                    ifroll =true;
                    print(ifafter);
                }
                if(r1!=r2) {
                    cout << r1<< " + " << r2 << " = " << r1+r2 << "  ";
                    cout << "You did not roll a double and you cannot leave." << endl;
                    ifafter=true;
                    ifroll =false;
                    print(ifafter);
                    
                }
            }
        }
        if(myplayer->can_leave_dc()) {
            cout << "You have stayed at DC Tims Line for three times, you paid 50$ to leave and now you may roll." <<endl;
            myplayer->set_money(-50);
            ifafter =false;
            ifroll = true;
            print(ifafter);
            
        }
    } return ifroll;
}
void read_cmd(shared_ptr<Player> myplayer,vector <shared_ptr<Player>> players,vector <string> players_name, vector <shared_ptr<Square>> squares,shared_ptr<Textdisplay>t,shared_ptr <Gameboard> g, int n) {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    print_turn(myplayer);
    print_before();
    bool ifafter=false;
    bool iftrade =false;
    bool ifimprove =true;
    int r1;
    int r2;
    int r = 0;
    string player_name=myplayer->get_name();
    bool can_roll =true;
    bool ifend =false;
    
    
    
    
    while(true){
        cin >> cmd;
        
        
        if(cmd== "test") {
            int n;
            cin>> n;
            while(true) {
                if(myplayer->get_money() < 0) {
                    cout << "Player " << myplayer->get_name() << " " << "needs to declare bankrupt or starts selling buildings." << endl;
                    break;
                }
                
                int myposition = myplayer->get_cur_square_num();//////////////////////////////////
                if((myposition==10)&&(myplayer->send_to())) {
                    cout << "You are at DC Tims Line, and you cannot leave unless you pay $50, or roll a double. " << endl;
                    if(!myplayer->can_leave_dc()) {
                        cout << "Would you like to pay?(y/n) " << endl;
                        string reply;
                        cin >> reply;
                        if(reply=="y") {
                            myplayer->set_money(-50);
                            if(bank_check(myplayer,players,g)) return;
                            cout << "You have paid $50, and you can roll again." <<endl;
                            ifafter= false;
                            print(ifafter);
                            break;
                        }
                        if(reply!="y") {
                            int r1 = myplayer->give_me_a_num()[0];
                            int r2 = myplayer->give_me_a_num()[1];
                            int cur = myplayer->get_position();
                            int r12 = r1 +r2;
                            if(r1==r2) {
                                //myplayer->set_position(cur+r12,false);
                                cout << *t;
                                cout << r1<< " + " << r2 << " = " << r1+r2 << "  ";
                                cout << "You rolled a double and you can leave DC Tims." <<endl;
                                ifafter =false;
                                print(ifafter);
                                break;
                                
                            }
                            if(r1!=r2) {
                                cout << r1<< " + " << r2 << " = " << r1+r2 << "  ";
                                cout << "You did not roll a double and you cannot leave." << endl;
                                ifafter=true;
                                print(ifafter);
                                break;
                            }
                        }
                    }
                    if(myplayer->can_leave_dc()) {
                        ifafter = false;
                        cout << "You have stayed at DC Tims Line for three times, you paid 50$ to leave and now you may roll." <<endl;
                        myplayer->set_money(-50);
                        if(bank_check(myplayer,players,g)) return ;
                        //	  if(ifend) return;
                        print(ifafter);
                        break;
                    }
                }
                myplayer->set_position(n,false);
                cout << *t;
                if(myplayer->can_collect_osap()) {
                    myplayer->set_money(200);
                    cout << "You have received $200 from OSAP!" << endl;
                }
                
                
                
                
                shared_ptr <Square> mysquare = myplayer->get_cur_square(); // i am waiting for phoebe to get building
                int a = myplayer->get_cur_square_num();
                ifimprove= true;
                
                bool ifend =  set_player(myplayer, ifimprove, players,g) ;
                if(ifend){
                    return;
                }
                
                print_after();
                ifafter=true;
                break;
                
                
                
            }
        }
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  roll dice
        else if(cmd== "roll") {
            getline(cin,cmd);
            istringstream ss{cmd};
            if((ss >> r1)&&(ss>>r2)) {
                while (true) {
                    if(!dc_tims(myplayer,players,ifafter, ifimprove, squares,t, g)) {
                        ifafter = true;
                        break;
                    }
                    if(ifafter)break;
                    if(player_name!=myplayer->get_name()) r =0;
                    player_name = myplayer->get_name();
                    int r12 = r1+r2;
                    shared_ptr <Square> mysquare = myplayer->get_cur_square();
                    int cur = mysquare->get_square_num();
                    if((r1==r2)&&(r<2)){
                        ++r;
                        //  set_player(myplayer,r1+r2);
                        ///////////////////// use helper to move to the right square;
                        
                        myplayer->set_position(cur+r12,false);
                        cout << *t;
                        cout << r1 << " + " << r2 << " = " << r1+r2 << endl;
                        cout << "Move forword " << r1+r2 << ". You have reached " << myplayer->get_cur_square()->get_square_name() << ". " << endl;
                        
                        osap(myplayer);
                        
                        set_player(myplayer,ifimprove,players,g);
                        cout << "You have rolled a double." << " You may roll again" << endl;
                        print(ifafter);
                        
                        break;
                    }
                    if((r1==r2)&&(r==2)) {
                        myplayer->set_position(10,false);
                        cout << *t;
                        cout << r1 << " + " << r2 << " = " << r1+r2 << endl;
                        cout << "You rolled three doubles, and you will be moved to DC Tims Line." << endl;
                        ifafter =true;
                        print(ifafter);
                        break;
                    }
                    if(r2!=r1) {
                        
                        /////////////////////////////// use helpter
                        myplayer->set_position(cur+r12,false);
                        cout << *t;
                        ifafter =true;
                        cout << r1 << " + " << r2 << " = " << r1+r2 << endl;
                        
                        
                        cout << "Move forword " << r1+r2 << ". You have reached " << myplayer->get_cur_square()->get_square_name() << ". " << endl;
                        osap(myplayer);
                        
                        set_player(myplayer,ifimprove,players,g);
                        print(ifafter);
                        break;
                    }
                    else {
                        cout << "Invalid set command." << endl;
                        break;
                    }
                    
                    
                }
            }
            
            
            
            
            
            
            
            
            else  {
                while (true) {
                    if(ifafter) {
                        cout << "You can no longer roll. Please enter next."<<endl;
                        print(ifafter);
                        break;
                    }
                    
                    if(!dc_tims(myplayer,players,ifafter, ifimprove, squares,t, g)) {
                        ifafter = true;
                        break;
                    }
                    if(ifafter)break;
                    if(player_name!=myplayer->get_name()) r =0;
                    player_name = myplayer->get_name();
                    int r1 = myplayer->give_me_a_num()[0];
                    int r2 = myplayer->give_me_a_num()[1];
                    int r12 = r1+r2;
                    shared_ptr <Square> mysquare = myplayer->get_cur_square();
                    int cur = mysquare->get_square_num();
                    if((r1==r2)&&(r<2)){
                        ++r;
                        //  set_player(myplayer,r1+r2);
                        ///////////////////// use helper to move to the right square;
                        
                        myplayer->set_position(cur+r12,false);
                        cout << *t;
                        cout << r1 << " + " << r2 << " = " << r1+r2 << endl;
                        cout << "Move forword " << r1+r2 << ". You have reached " << myplayer->get_cur_square()->get_square_name() << ". " << endl;
                        
                        osap(myplayer);
                        set_player(myplayer,ifimprove,players,g);
                        
                        cout << "You have rolled a double." << " You may roll again" << endl;
                        print(ifafter);
                        break;
                    }
                    if((r1==r2)&&(r==2)) {
                        myplayer->set_position(10,false);
                        cout << *t;
                        cout << r1 << " + " << r2 << " = " << r1+r2 << endl;
                        cout << "You rolled three doubles, and you will be moved to DC Tims Line." << endl;
                        ifafter =true;
                        ifimprove = true;
                        print(ifafter);
                        break;
                    }
                    if(r2!=r1) {
                        
                        /////////////////////////////// use helpter
                        myplayer->set_position(cur+r12,false);
                        cout << *t;
                        ifafter =true;
                        cout << r1 << " + " << r2 << " = " << r1+r2 << endl;
                        cout << "Move forword " << r1+r2 << ". You have reached " << myplayer->get_cur_square()->get_square_name() << ". " << endl;
                        osap(myplayer);
                        set_player(myplayer,ifimprove,players,g);
                        print(ifafter);
                        break;
                    }
                    else {
                        break;
                    }
                    
                    
                }
            }
        }
        
        
        
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        
        
        else if(cmd=="next") {
            if(ifafter){
                myplayer=myplayer->get_next_player();
                print_turn(myplayer);
                ifafter=false;
                ifimprove=true;
                print_before();
            } else {
                cout << "It's your turn and you need to roll" << endl;
            }
        }
        else if(cmd=="exit")return;
        else if(cmd=="help") {
            string h;
            ifstream file{"help.txt"};
            for(int i = 0; i < 9; ++i) {
                getline(file,h);
                cout << h << endl;
            }
            print(ifafter);
        }
        
        else if(cmd=="all") {
            for(int i =0; i < players.size(); ++i) {
                cout << "Player " << players[i]->get_name() << " has $" << players[i]->get_money() << "." << endl;
                cout << "Roll Up the Rim Cup: " << players[i]->get_num_roll() <<endl ;
                cout << "Buildings: " ;
                for(int j =0; j < players[i]->my_building().size();++j) {
                    cout << players[i]->my_building()[j]->get_square_name()<< " "  ;
                    cout << players[i]->my_building()[j]->get_cur_improvement() << " " ;
                } cout <<endl;
                cout <<endl;
            }
            print(ifafter);
            
        }
        
        
        
        
        
        else if(cmd=="asset") {
            cout << "Player " << myplayer->get_name() << " has $" << myplayer->get_money() << "." << endl;
            cout << "Roll Up the Rim Cup: " << myplayer->get_num_roll() <<endl;
            cout << "Buildings you have : " << endl;
            
            for(int i =0; i < (myplayer->my_building()).size();++i) {
                cout << myplayer->my_building()[i]->get_square_name()<< " "  ;
                cout << myplayer->my_building()[i]->get_cur_improvement() << endl;
            }
            print(ifafter);
            
        }
        
        else if(cmd=="mortgage") {
            string building;
            cin >> building;
            
            shared_ptr <Ownable> myown = myplayer->building_in_list(building);
            if(myown&&(!myown->is_mortgage())&&(!myown->check_block())) {
                myplayer->mortgage_building(myown);
                cout << "You have mortgaged " << myown->get_square_name() << "." << endl;
            }
            else {
                cout << "Invalid mortgage." << endl;
            }
            
            
        }
        
        
        
        
        else if(cmd=="unmortgage") {
            string building;
            cin >> building;
            
            shared_ptr <Ownable> myown = myplayer->building_in_list(building);
            if(myown&&(myown->is_mortgage())) {
                myplayer->unmortgage_building(myown);
                cout << "You have unmortgaged your building " << myown->get_square_name() << "." << endl;
            }
            else {
                cout << "Invalid unmortgage." << endl;
            }
            
        }
        
        
        
        ////////////////////////////////////////////////////
        else if(cmd=="improve") {
            shared_ptr <Square> mysquare = myplayer->get_cur_square();
            
            while(true) {
                string improvement;
                getline(cin,improvement);
                istringstream ss{improvement};
                string building;
                ss >> building;
                
                ss >> cmd;
                
                if((mysquare->get_square_name()!=building)&&(cmd=="buy")) {
                    cout << "You can only improve a building when you land on it." << endl;
                    print(ifafter);
                    break;
                }
                
                if(!myplayer->building_in_list(building)) {
                    cout << "You do not have the building " << building << ". Please check again." << endl;
                    print(ifafter);
                    break;
                }
                
                if(!dynamic_pointer_cast<Academic> (myplayer->building_in_list(building))) {
                    cout << "Invalid command. You can only improve an academic building." << endl;
                    print(ifafter);
                    break;
                }
                
                
                shared_ptr <Academic> mybuilding  = dynamic_pointer_cast<Academic> (myplayer->building_in_list(building));
                if(ifimprove&&(cmd=="buy")&&(mybuilding->can_improve())&&(mybuilding->get_improvement_cost()<=myplayer->get_money())) {
                    mybuilding->buy_improve();
                    cout << "You have improved your building " << mybuilding->get_square_name() << "." << endl;
                    
                    mybuilding->set_rent();
                    
                    ifimprove=false;
                    
                    
                }
                else if(ifimprove&&(cmd=="buy")&&(mybuilding->can_improve())&&(mybuilding->get_improvement_cost()>myplayer->get_money())) {
                    cout << "You do not have enough money." <<endl;
                }
                else if((cmd=="sell")&&(mybuilding->can_sell_improve())) {
                    mybuilding->sell_improve();
                    mybuilding->set_rent();
                    cout << "You have successfully sold an improment on " <<  mybuilding->get_square_name() << "." << endl;
                    
                }
                else if((cmd=="buy")&&(!mybuilding->can_improve())) {
                    cout << "Your building cannot be improved." << endl;
                    
                }
                else  if((cmd=="sell")&&(!mybuilding->can_sell_improve())) {
                    cout << "There is no improvement can be sold." << endl;
                    
                }
                else {
                    cout << "Invalid improvement command, you may enter help to check instructions." << endl;
                }
                
                cout << *t;
                print(ifafter);
                break;
            }
        }
        
        
        
        
        
        
        
        else if(cmd=="trade") {
            
            string trading;
            getline(cin, trading);
            istringstream  ss  {trading};
            string player2;
            ss >> player2;
            
            int playernum = 0;
            for(int i =0; i < n; ++i) {
                if(players_name[i]==player2) {
                    iftrade = true;
                    playernum = i;
                    
                }
            }
            if(!iftrade) {
                cout << "Invalid player name. " << endl;
                if(ifafter) print_after();
                if(!ifafter) print_before();
                break;
            }
            
            
            string object1;
            string object2;
            
            
            ss >> object1;
            ss >> object2;
            int cash1;
            int cash2;
            
            bool ifbuy = false;
            bool ifsell = false;
            bool ifexchange = false;
            istringstream s1 {object1};
            istringstream s2 {object2};
            
            if((s1 >> cash1)&&(players[playernum]->building_in_list(object2))&&(!((players[playernum])->building_in_list(object2))->check_block())) {
                if (myplayer->get_money() < cash1) {
                    cout << "You do not have enough money to trade." << endl;
                }
                else {
                    cout << players[playernum]->get_name() << ", would you like to sell your building " << object2 << " to ";
                    cout << myplayer->get_name() << " for " << cash1 << "$?(y/n) " << endl;
                    string yes;
                    cin >> yes;
                    if(yes=="y")  {
                        ifbuy = true;
                    }
                    else {
                        cout << "Trade failed." << endl;
                        print(ifafter);
                    }
                }
            }
            if((s2 >> cash2)&&(myplayer->building_in_list(object1))&&(!(myplayer->building_in_list(object1))->check_block())) {
                if(players[playernum]->get_money() < cash2) {
                    cout << players[playernum]->get_name() << " do not have enough money ro trade," << endl;
                }
                else {
                    cout << players[playernum]->get_name() << ", would you like to buy "  << object2 << " from ";
                    cout << myplayer->get_name() << " for "<< cash2 << "$?(y/n) " << endl;
                    string yes;
                    cin >> yes;
                    if(yes=="y") ifsell = true;
                    
                    else {
                        cout << "Trade failed." << endl;
                        print(ifafter);
                    }
                }
            }
            if((myplayer->building_in_list(object1))&&(players[playernum]->building_in_list(object2))&&(!(myplayer->building_in_list(object1))->check_block())&&(!((players[playernum])->building_in_list(object2))->check_block())) {
                cout << players[playernum]->get_name() << ", would you like to give "  <<  myplayer->get_name();
                cout <<" " <<  object2 << " inexchange for " << object1 << "? " << endl;
                string yes;
                cin >> yes;
                if(yes=="y") ifexchange = true;
                else {
                    cout << "Trade failed." << endl;
                    print(ifafter);
                    vector <shared_ptr<Player>> players;
                }
            }
            bool invalid =true;
            if(ifbuy||ifsell||ifexchange)  invalid =false;
            if(invalid) {
                cout << "Invalid trade. "  << endl;
                print(ifafter);
            }
            
            
            
            
            if(ifbuy) {
                g->trade(players[playernum],myplayer,cash1,object2);
                cout << myplayer->get_name() << " has bought " << object1 << " from " << players[playernum]->get_name()  << endl;
                
                print(ifafter);
            }
            if(ifsell) {
                g->trade(myplayer,players[playernum],cash2,object1);
                cout <<"after  " <<endl;
                cout << myplayer->get_name() << " has bought " << object1 << " from " << players[playernum]->get_name()  << endl;
                print(ifafter);
            }
            if(ifexchange) {
                g->trade(myplayer,players[playernum],object1,object2);
                cout << myplayer->get_name() << " has given " << object1 << " to " << players[playernum]->get_name() << " inexchange for " << object2 << endl;
                print(ifafter);
            }
        }
        
        else if(cmd=="save") {
            ofstream file;
            string filename;
            cin >> filename;
            istringstream ss{filename};
            file.open(filename.c_str());
            file << n << endl;
            int j =0;
            while(j<players.size()) {
                file << myplayer->get_name() << " " << myplayer->get_char() << " " <<myplayer->get_num_roll() <<" " << myplayer->get_money() << " " ;
                file << myplayer->get_cur_square()->get_square_num() << endl;
                ++j;
                myplayer = myplayer->get_next_player();
            }
            // for (int i =0; i < n; ++i) {
            // file << players[i]->get_name() << " " << players[i]->get_char() << " " << players[i]->get_num_roll() <<" "  <<  players[i]->get_money() << " "  ;
            //file << players[i]->get_cur_square()->get_square_num() << endl;
            // }
            for(int i = 0; i < 40; ++i) {
                shared_ptr <Ownable> tmp  = dynamic_pointer_cast<Ownable>(squares[i]);
                if(tmp!=nullptr) {
                    file << tmp->get_square_name() << " " ;
                    if(tmp->can_own()) {
                        file << "BANK " ;
                    }
                    if(!tmp->can_own()) {
                        file << tmp->get_owner() << " " ;
                    }
                    if(tmp->is_mortgage()) {
                        file << "-1" << endl;
                    }
                    if(!tmp->is_mortgage()) {
                        file << tmp->get_cur_improvement() << endl;
                    }
                    
                }
            }
            file.close();
            break;
        }
    }
}

bool if_in_list(shared_ptr<Player> cur_player,vector<shared_ptr<Player>> withdraws) {
    for(int i=0; i < withdraws.size(); ++i) {
        if(withdraws[i]==cur_player) return true;
    } return false;
}

void host_auction(shared_ptr<Ownable> myown, shared_ptr<Player> myplayer, vector <shared_ptr<Player>> players) {
    int cost = 0;
    bool win = false;
    string building_name = myown->get_square_name();
    string cmd;
    int num;
    vector <shared_ptr<Player>> withdraws;
    withdraws.emplace_back(myplayer);
    cout << "Auction begins!" << endl;
    string  winner;
    while (true) {
        for(int i =0; i < players.size(); ++i) {
            while(!if_in_list(players[i],withdraws)) {
                cout << "Buiding : " << building_name << endl;
                cout << "Current Bid:" << cost << endl;
                cout << players[i]->get_name() << ", would you like to rise the price or withdraw? (r/w)" << endl;
                cin >> cmd;
                if(cmd=="r") {
                    cout << "Please enter the amount you would like to pay. " << endl;
                    if((cin >> num)&&(num>cost)&&(players[i]->get_money()>=num)) {
                        cout << "You have succussfully rose the price of the building." <<endl;
                        cost = num;
                        winner=players[i]->get_name();
                        break;
                    }
                    else {
                        cout << "Invalid amount!! Check if you have enough money, or the amount you rise is less than current bid." <<endl;
                    }
                }
                if(cmd=="w") {
                    if(withdraws.size()+1<players.size()) {
                        withdraws.emplace_back(players[i]);
                        cout << "You have withdrawn from the auction." << endl;
                    }
                    else{
                        win =true;
                        cout << "You are the player left in the auction, you will receive the building." <<endl;
                        break;
                    }
                    
                }
            }
        } if(cost ==0) {
            for(int i = 0; i < players.size(); ++i) {
                if(!if_in_list(players[i],withdraws)) {
                    win = true;
                    winner=players[i]->get_name();
                }
            }
        }
        if(win) break;
        if(players.size()==withdraws.size()+1) break;
    }
    cout << "Auction ends! " << endl;
    
    for(int i = 0; i < players.size(); ++i) {
        if(winner==players[i]->get_name()) {
            players[i]->buy_building(myown,cost);
            cout << winner << " has bought " << building_name << " for " << cost  << "$"  << endl;
            break;
        }
    }
}




bool set_player(shared_ptr<Player> myplayer, bool ifimprove, vector <shared_ptr<Player>> players,shared_ptr <Gameboard> g) {
    //   myplayer->set_position(move,false);
    bool endgame =false;
    string cmd;
    shared_ptr <Square> mysquare = myplayer->get_cur_square();
    if(mysquare->is_ownable()) {
        shared_ptr <Ownable> tmp  = dynamic_pointer_cast<Ownable>(mysquare);
        bool ifowner= false;
        bool first = true;
        if(tmp->get_owner()==myplayer->get_name()) ifowner= true;
        if(tmp->can_own()) {
            first = false;
            cout << "The purchase cost of building " << mysquare->get_square_name() << " is ";
            cout << tmp->get_purchase_cost() << "$. " << endl;
            cout << "Would you like to buy it? (y/n)" << endl;
            cin >> cmd;
            if((cmd=="y")&&(myplayer->get_money()>=tmp->get_purchase_cost())) {
                myplayer->buy_building(tmp,tmp->get_purchase_cost());
                cout << "You have purchased " << tmp->get_square_name() << endl;
                tmp->set_rent();
                ifimprove =false;
            }
            if((cmd=="y")&&(myplayer->get_money()<tmp->get_purchase_cost())) {
                cout << "You do not have enough money."<< endl;
                host_auction(tmp, myplayer, players);
            }
            if(cmd!="y") {
                host_auction(tmp,myplayer, players);
            }
        }
        if(first&&ifowner) {
            cout << "You have landed on a building you owned. " << endl;
            shared_ptr <Academic> ifacademic = dynamic_pointer_cast<Academic>(mysquare);
            if((ifacademic!=nullptr)&&(ifacademic->can_improve())&&(myplayer->get_money() >= ifacademic->get_improvement_cost())) {
                cout << "You may improve your building." << endl;
            }
            if((ifacademic!=nullptr)&&(ifacademic->can_improve())&&(myplayer->get_money() < ifacademic->get_improvement_cost())) {
                cout << "You do not have enough money." << endl;
            }
        }
        if(first&&(!ifowner)&&(!tmp->can_own())&&(!tmp->is_mortgage())) {
            cout << "You have landed on " << mysquare->get_square_name();
            cout << ". The owner of the building is " << tmp->get_owner() << "." << endl;
            shared_ptr <Gym> ifgym = dynamic_pointer_cast<Gym>(mysquare);
            if(ifgym!=nullptr) {
                cout << "Roll dice to determine how much you need to pay, please enter anything to roll!" <<endl;
                if( cin >> cmd) {
                    int r1 = myplayer->give_me_a_num()[0];
                    int r2 = myplayer->give_me_a_num()[1];
                    int r12 = r1+r2;
                    cout << r1 << " + " << r2 << " = " << r1+r2 << endl;
                    ifgym->set_rent(r12);
                    
                    ifgym->pay_rent(myplayer);
                    cout << "You have paid $" << ifgym->get_rent() << " to " << ifgym->get_owner() << endl;
                }
            }
            if(ifgym==nullptr) {
                shared_ptr <Ownable> ifacademic = dynamic_pointer_cast<Ownable>(mysquare);
                ifacademic->pay_rent(myplayer);
                cout << "You have paid $" << ifacademic->get_rent() << " to " << ifacademic->get_owner() << endl;
                ifacademic->get_cur_owner()->set_money(myplayer->get_money());
                if(myplayer->get_money() < 0) {
                    for(int i = 0;i <myplayer->my_building().size(); ++i) {
                        myplayer->my_building()[i]->set_owner(ifacademic->get_cur_owner());
                    }
                    myplayer->transfer_roll(ifacademic->get_cur_owner());
                    cout << "You owned $" << ifacademic->get_owner() <<  0-myplayer->get_money() << ". You went bankrupt and " << ifacademic->get_owner() << " received all your assets!"<<endl;
                    string left =myplayer->get_name();
                    bool ifend = g->kick_out(myplayer);
                    cout << left << " has left the game!" << endl;
                    if(ifend) {
                        for(int i = 0; i < players.size(); ++i) {
                            if(left!=players[i]->get_name()) {
                                cout << players[i]->get_name() << " is the winner! The game ends!" << endl;
                                return true;
                            }
                            
                        }
                    }
                    
                }
                
            }
        }
        if (first&&(!ifowner)&&(!tmp->can_own())&&(tmp->is_mortgage())) {
            cout << "You have landed on " << tmp->get_square_name();
            cout << ". The owner of the building is " << tmp->get_owner() << "." << endl;
            cout << "The building has been mortgaged, you do not need to pay anything." << endl;
        }
    }
    else {
        string non_own = mysquare->get_square_name();
        if(non_own == "SLC") {
            shared_ptr <SLC> tmp  = dynamic_pointer_cast<SLC>(myplayer->get_cur_square());
            bool ifchance = g->can_get_roll();
            cmd = tmp->calculus(ifchance);
            if(cmd== "receive a winning Roll Up the Rim cup") {
                g->set_num_roll(-1);
                myplayer->set_rolluprim(1);
            }
            else{
                int move = tmp->go_to(myplayer,cmd);
                cout << cmd << endl;
                myplayer->set_position(move,false);
                set_player(myplayer,ifimprove,players,g);
                cmd = tmp->calculus(ifchance);
            }
        }
        
        if(non_own == "NEEDLES HALL"){
            bool ifchance = g->can_get_roll();
            shared_ptr <Needles> tmp  = dynamic_pointer_cast<Needles>(mysquare);
            cmd = tmp->calculus(ifchance);
            if(cmd== "receive a winning Roll Up the Rim cup") {
                g->set_num_roll(-1);
                myplayer->set_rolluprim(1);
            }
            else {
                shared_ptr <Needles> tmp  = dynamic_pointer_cast<Needles>(myplayer->get_cur_square());
                tmp->mutate_money(myplayer, cmd);
                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        /////////////////////////////////////////////////////////////////////
                if(bank_check(myplayer,players,g)) return true;
                
                
                
                /////////////////////////////////////////////////////////////////////////////////////////////////////////
                
                cout << cmd << endl;
            }
        }
        if(non_own == "Goose Nesting") {
            cout << "You are attacked by a flock of nesting geese!" << endl;
        }
        if(non_own == "TUITION" ) {
            while(true) {
                cout << "Choose between paying $300 tuition or 10 percent of your total worth (including your savings, printed prices of all buildings you own, and costs of each improvement).(1/2)" << endl;
                cout << "1.$300 tuition" << endl;
                cout << "2.10 percent of your total worth" << endl;
                int choice;
                cin >>  choice;
                if(choice==1) {
                    myplayer->set_money(-300);
                    if(bank_check(myplayer,players,g)) return true;
                    cout << " You paid 300$ tuition to school." << endl;
                    break;
                }
                if(choice == 2) {
                    int payment = 0-myplayer->tuition();
                    myplayer->set_money(payment);
                    if(bank_check(myplayer,players,g)) return true;
                    cout << "You have paid " << myplayer->tuition() << "$ to school" << endl;
                    break;
                }
            }
        }
        if(non_own =="COOP FEE" ) {
            bool ifend = false;
            myplayer->set_money(-150);
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if(myplayer->get_money() <0) {
                cout << "You owned bank money, you need to enter bankrupt to declare bankruptcy." <<endl;
                while(true) {
                    string b;
                    cin >> b;
                    if(b=="bankrupt") break;
                    cout << "You can only enter bankrupt." << endl;
                }
                vector <shared_ptr<Ownable>> auction_list;
                for(int i =0; i < myplayer->my_building().size();++i) {
                    auction_list.emplace_back(myplayer->my_building()[i]);
                }
                int j = auction_list.size()-1;
                while(j>0) {
                    g->return_to_market(myplayer->my_building()[j]);
                    --j;
                }
                for(int i = 0; i < auction_list.size(); ++i) {
                    host_auction(auction_list[i], myplayer, players);
                }
                cout << myplayer->get_name() << "'s proproties has been divided." << endl;
                string left =myplayer->get_name();
                ifend = g->kick_out(myplayer);
                cout << left << " has left the game!" << endl;
                
                if(ifend) {
                    for(int i = 0; i < players.size(); ++i) {
                        if(left!=players[i]->get_name()) {
                            cout << players[i]->get_name() << " is the winner! The game ends!" << endl;
                        }
                    }
                    //     if(ifend) return ifend;
                    return true;
                }
            }
            
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////
            cout << " You paid 150$ coop fee to school." << endl;
        }
        if(non_own == "GO TO TIMS") {
            myplayer->set_position(10,true);
            cout << *(g->get_text());
            cout << "You landed on Go to Tims, you have been sent to DC Tims line" << endl;
        }
        if(non_own == "DC Tims Line" ) {
            cout << "You are at DC Tims Line." << endl;
            
        }
        
    } // if(ifend) {
    // cout << "set player ifend" << endl;
    // }
    //return ifend;
    return false;
    
}










