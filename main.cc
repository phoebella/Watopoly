#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "Gameboard.h"
#include "Player.h"
#include "Textdisplay.h"
#include "Square.h"
#include "Gym.h"
#include "Rez.h"
#include "Nonownable.h"
#include "Academic.h"
#include "Nonacademic.h"
#include "Ownable.h"
#include "SLC.h"
#include "Needles.h"
#include "helper.h"
using namespace std;




int main(int argc, char * argv[]) {
    bool second = false;
    bool newgame = false;
    if(argc==1) {
        //cout << "testing" ;
        newgame = true;
        //... and we load the game.......
        
    }
    if(argc == 3) second = true;
    
    
    
    ifstream file{"map.txt"};
    string myline;
    int board_length = 89; //change to 89 later
    int board_height = 56; //change to 56 later
    vector <vector<char>> myboard;
    
    for(int j = 0; j < board_height; ++j) {
        getline(file,myline);
        vector <char> myrow;
        for (int i =0; i < board_length; ++i) {
            char mychar = myline[i];
            myrow.push_back(mychar);
        } myboard.push_back(myrow);
    }
    
    
    // we read in the command
    
    //cin.exceptions(ios::eofbit|ios::failbit);
    // string cmd
    //cout << "test" << "4" << mysquare->get_square_name() << "    " <<endl;
    //Gameboard g;
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   a new game initializatio:500n
    if(second) {
        cout << "Welcome back to Watopoly!" <<endl;
        // string filename(argv[2]);
        ifstream oldgame;
        oldgame.exceptions(ifstream::failbit|ifstream::eofbit);
        string s{argv[2]};
        while(true){
            try{
               oldgame.open(s.c_str());
                break;
            }
            catch(ios::failure){
                cout << "file doesn't exist, try again ";
                cin >> s;
            }
        }
        
        // ifstream oldgame{"game.txt"};
        string line;
        
        getline(oldgame,line);
        
        int n;
        istringstream ss{line};
        vector <string> players_name;
        vector <char> players_char;
        vector <int> players_money;
        vector <int> players_square;
        vector <int> players_rim;
        ss >> n;
        for (int i = 0; i < n; ++i) {
            getline(oldgame,line);
            istringstream ss{line};
            string myname;
            ss >> myname;
            players_name.emplace_back(myname);
            char mychar;
            ss >> mychar;
            players_char.emplace_back(mychar);
            int myrim;
            ss >> myrim;
            players_rim.emplace_back(myrim);
            int mymoney;
            ss >> mymoney;
            players_money.emplace_back(mymoney);
            int pos;
            ss >> pos;
            players_square.emplace_back(pos);
        }
        //1
        
        
        auto AL = make_shared<Academic>(Academic("AL",54,73,true,1,40,"Arts1",2,nullptr,51,73,50,10,30,90,160,250));
        auto ML = make_shared<Academic>(Academic("ML",54,57,true,3,60,"Arts1",4,nullptr,51,57,50,20,60,180,320,450));
        vector <shared_ptr<Ownable>> acd1;
        acd1.emplace_back(AL);
        acd1.emplace_back(ML);
        AL->set_monopoly_list(acd1);
        ML->set_monopoly_list(acd1);
        
        
        
        
        auto ECH = make_shared<Academic>(Academic("ECH",54,33,true,6,100,"Arts2",6,nullptr,51,33,50,30,90,270,400,550));
        auto PAS = make_shared<Academic>(Academic("PAS",54,17,true,8,100,"Arts2",6,nullptr,51,17,50,30,90,270,400,550));
        auto HH = make_shared<Academic>(Academic("HH",54,9,true,9,120,"Arts2",8,nullptr,51,9,50,40,100,300,450,600));
        vector <shared_ptr<Ownable>> acd2;
        acd2.emplace_back(ECH);
        acd2.emplace_back(PAS);
        acd2.emplace_back(HH);
        ECH->set_monopoly_list(acd2);
        PAS->set_monopoly_list(acd2);
        HH->set_monopoly_list(acd2);
        
        
        
        auto RCH = make_shared<Academic>(Academic("RCH",49,1,true,11,140,"Eng",10,nullptr,46,1,100,50,150,450,625,750));
        auto DWE = make_shared<Academic>(Academic("DWE",39,1,true,13,140,"Eng",10,nullptr,36,1,100,50,150,450,625,750));
        auto CPH = make_shared<Academic>(Academic("CPH",34,1,true,14,160,"Eng",12,nullptr,31,1,100,60,180,500,700,900));
        vector <shared_ptr<Ownable>> acd3;
        acd3.emplace_back(RCH);
        acd3.emplace_back(DWE);
        acd3.emplace_back(CPH);
        RCH->set_monopoly_list(acd3);
        DWE->set_monopoly_list(acd3);
        CPH->set_monopoly_list(acd3);
        
        
        
        auto LHI = make_shared<Academic>(Academic("LHI",24,1,true,16,180,"Health",14,nullptr,21,1,100,70,200,550,750,950));
        auto BMH = make_shared<Academic>(Academic("BMH",14,1,true,18,180,"Health",14,nullptr,11,1,100,70,200,550,750,950));
        auto OPT = make_shared<Academic>(Academic("OPT",9,1,true,19,200,"Health",16,nullptr,6,1,100,80,220,600,800,1000));
        vector <shared_ptr<Ownable>> acd4;
        acd4.emplace_back(LHI);
        acd4.emplace_back(BMH);
        acd4.emplace_back(OPT);
        LHI->set_monopoly_list(acd4);
        BMH->set_monopoly_list(acd4);
        OPT->set_monopoly_list(acd4);
        
        
        auto EV1 = make_shared<Academic>(Academic("EV1",4,9,true,21,220,"Env",18,nullptr,1,9,150,90,250,700,875,1050));
        auto EV2 = make_shared<Academic>(Academic("EV2",4,25,true,23,220,"Env",18,nullptr,1,25,150,90,250,700,875,1050));
        auto EV3 = make_shared<Academic>(Academic("EV3",4,33,true,24,240,"Env",20,nullptr,1,33,150,100,300,50,925,1100));
        vector <shared_ptr<Ownable>> acd5;
        acd5.emplace_back(EV1);
        acd5.emplace_back(EV2);
        acd5.emplace_back(EV3);
        EV1->set_monopoly_list(acd5);
        EV2->set_monopoly_list(acd5);
        EV3->set_monopoly_list(acd5);
        
        
        auto PHYS = make_shared<Academic>(Academic("PHYS",4,49,true,26,260,"Sci1",22,nullptr,1,49,150,110,330,800,975,1150));
        auto B1 = make_shared<Academic>(Academic("B1",4,57,true,27,260,"Sci1",22,nullptr,1,57,150,110,330,800,975,1150));
        auto B2 = make_shared<Academic>(Academic("B2",4,73,true,29,280,"Sci1",24,nullptr,1,73,150,120,360,850,1025,1200));
        vector <shared_ptr<Ownable>> acd6;
        acd6.emplace_back(PHYS);
        acd6.emplace_back(B1);
        acd6.emplace_back(B2);
        PHYS->set_monopoly_list(acd6);
        B1->set_monopoly_list(acd6);
        B2->set_monopoly_list(acd6);
        
        
        auto EIT= make_shared<Academic>(Academic("EIT",9,81,true,31,300,"Sci2",26,nullptr,6,81,200,130,390,900,1100,1275));
        auto ESC = make_shared<Academic>(Academic("ESC",14,81,true,32,300,"Sci2",26,nullptr,11,81,200,130,390,900,1100,1275));
        auto C2 = make_shared<Academic>(Academic("C2",24,81,true,34,320,"Sci2",28,nullptr,21,81,200,150,450,1000,1200,1400));
        vector <shared_ptr<Ownable>> acd7;
        acd7.emplace_back(EIT);
        acd7.emplace_back(ESC);
        acd7.emplace_back(C2);
        EIT->set_monopoly_list(acd7);
        ESC->set_monopoly_list(acd7);
        C2->set_monopoly_list(acd7);
        
        
        auto MC = make_shared<Academic>(Academic("MC",39,81,true,37,350,"Math",35,nullptr,36,81,200,175,500,1100,1300,1500));
        auto DC = make_shared<Academic>(Academic("DC",49,81,true,39,400,"Math",50,nullptr,46,81,200,200,600,1400,1700,2000));
        vector <shared_ptr<Ownable>> acd8;
        acd8.emplace_back(MC);
        acd8.emplace_back(DC);
        MC->set_monopoly_list(acd8);
        DC->set_monopoly_list(acd8);
        
        
        auto PAC = make_shared<Gym>(Gym("PAC",44,1,true,12,150,"Gym",0,nullptr));
        auto CIF = make_shared<Gym>(Gym("CIF",4,65,true,28,150,"Gym",0,nullptr));
        vector <shared_ptr<Ownable>> gym;
        gym.emplace_back(PAC);
        gym.emplace_back(CIF);
        PAC->set_monopoly_list(gym);
        CIF->set_monopoly_list(gym);
        
        
        
        auto MKV = make_shared<Rez>(Rez("MKV",54,41,true,5,200,"Rez",0,nullptr));
        auto UWP = make_shared<Rez>(Rez("UWP",29,1,true,15,200,"Rez",0,nullptr));
        auto V1 = make_shared<Rez>(Rez("V1",4,41,true,25,200,"Rez",0,nullptr));
        auto REV = make_shared<Rez>(Rez("REV",29,81,true,35,200,"Rez",0,nullptr));
        vector <shared_ptr<Ownable>> rez;
        rez.emplace_back(MKV);
        rez.emplace_back(UWP);
        rez.emplace_back(V1);
        rez.emplace_back(REV);
        MKV->set_monopoly_list(rez);
        UWP->set_monopoly_list(rez);
        V1->set_monopoly_list(rez);
        REV->set_monopoly_list(rez);
        
        
        
        auto OSAP = make_shared<Nonownable>(Nonownable("COLLECT OSAP",54,81,false,0));
        auto SLC1 = make_shared<SLC>(SLC("SLC",54,65,false,2));  // SLC1
        auto TUITION = make_shared<Nonownable>(Nonownable("TUITION",54,49,false,4));
        auto NH1 = make_shared<Needles>(Needles("NEEDLES HALL",54,25,false,7)); //NEEDLES HALL : NH
        auto DCT = make_shared<Nonownable>(Nonownable("DC Tims Line",54,1,false,10));//DC Tims : DCT
        auto SLC2 = make_shared<SLC>(SLC("SLC",19,1,false,17));
        auto GN = make_shared<Nonownable>(Nonownable("Goose Nesting",4,1,false,20));
        auto NH2 = make_shared<Needles>(Needles("NEEDLES HALL",4,17,false,22));
        auto GTT = make_shared<Nonownable>(Nonownable("GO TO TIMS",4,81,false,30));
        auto SLC3 = make_shared<SLC>(SLC("SLC",19,81,false,33));
        auto NH3 = make_shared<Needles>(Needles("NEEDLES HALL",34,81,false,36));
        auto CF = make_shared<Nonownable>(Nonownable("COOP FEE",44,81,false,38));
        
        
        
        
        vector <shared_ptr<Square>> squares;
        
        
        squares.emplace_back(OSAP);
        squares.emplace_back(AL);
        squares.emplace_back(SLC1);
        squares.emplace_back(ML);
        squares.emplace_back(TUITION);
        squares.emplace_back(MKV);
        squares.emplace_back(ECH);
        squares.emplace_back(NH1);
        squares.emplace_back(PAS);
        squares.emplace_back(HH);
        squares.emplace_back(DCT);
        squares.emplace_back(RCH);
        squares.emplace_back(PAC);
        squares.emplace_back(DWE);
        squares.emplace_back(CPH);
        squares.emplace_back(UWP);
        squares.emplace_back(LHI);
        squares.emplace_back(SLC2);
        squares.emplace_back(BMH);
        squares.emplace_back(OPT);
        squares.emplace_back(GN);
        squares.emplace_back(EV1);
        squares.emplace_back(NH2);
        squares.emplace_back(EV2);
        squares.emplace_back(EV3);
        squares.emplace_back(V1);
        squares.emplace_back(PHYS);
        squares.emplace_back(B1);
        squares.emplace_back(CIF);
        squares.emplace_back(B2);
        squares.emplace_back(GTT);
        squares.emplace_back(EIT);
        squares.emplace_back(ESC);
        squares.emplace_back(SLC3);
        squares.emplace_back(C2);
        squares.emplace_back(REV);
        squares.emplace_back(NH3);
        squares.emplace_back(MC);
        squares.emplace_back(CF);
        squares.emplace_back(DC);
        
        auto t = make_shared<Textdisplay>(Textdisplay(myboard));
        vector <shared_ptr<Player>> players;
        int total_rim =0;
        for(int i = 0; i < n; ++i) {
            total_rim += players_rim[i];
            auto a = players_name[i];
            auto b = players_char[i];
            auto c = squares;
            auto d = squares[players_square[i]];
            auto e = squares[players_square[i]];
            auto f =t;
            auto q = make_shared<Player>(Player(a,b,players_rim[i],c,i,d,nullptr,f));
            q->set_position(players_square[i],false);
            q->set_money(-1500);
            q->set_money(players_money[i]);
            players.emplace_back(q);
        }
        for(int i = 0; i < n-1;++i) {
            players[i]->set_next_player(players[i+1]);
        }
        players[n-1]->set_next_player(players[0]);
        vector <string> ownables;
        vector <string> owners;
        vector <int> states;
        for (int i = 0; i < 28; ++i) {
            getline(oldgame,line);
            istringstream ss{line};
            string ownable;
            ss >> ownable;
            ownables.emplace_back(ownable);
            string owner;
            ss >> owner;
            owners.emplace_back(owner);
            int state;
            ss >> state;
            states.emplace_back(state);
        }
        for (int i = 0 ; i < 28; ++i) {
            if(owners[i]!="BANK") {
                for(int j =0; j < n; ++j) {
                    if(players[j]->get_name()==owners[i]) {
                        for(int k = 0; k < 40; ++k) {
                            if(squares[k]->get_square_name()==ownables[i]) {
                                shared_ptr <Ownable> tmp1 = dynamic_pointer_cast<Ownable> (squares[k]);
                                tmp1->set_owner(players[j]);
                                if(states[i]<0) {
                                    tmp1->change_mortgage();
                                }
                                shared_ptr <Academic> tmp2  = dynamic_pointer_cast<Academic> (tmp1);
                                if((tmp2!=nullptr)&&(states[i]>0)) {
                                    tmp2->set_improvement(states[i]);
                                }
                                //break;
                            }
                        }
                        //break;
                    }
                }
            }
        }
        Gameboard mygameboard{n,4-total_rim,players,players[0],squares,t};
        auto g = make_shared<Gameboard>(Gameboard(mygameboard));
        cout << *t;
        read_cmd(players[0], players, players_name, squares, t, g, n);
        
    }
    
    
    
    
    
    
    
    
    
    if(newgame) {
        cout << "Wellcome to the Watopoly!"<< endl;
        cout << "Please enter the number of players (from 2 to 7)!" << endl;
        int n;
        bool valid = true;
        while (true) {
            if(!(cin>>n)) {
                cin.clear();
                cin.ignore();
                valid = false;
                cout <<"Please enter a number! " << endl;
                
            }
            else {
                valid =true;
                if((n>7) ||(n<2)) {
                    cout << "Out of range, please enter a number from 2 to 7!" << endl;
                    valid =false;
                }
            }
            if(valid) break;
        } //n players succussfully joined the game!
        
        
        cout << n << " players joined the game!" << endl;
        int numplayer =0;
        vector <char> players_char ;
        vector <string> players_name;
        /*char players_char[n];
         string players_name[n];*/
        const string myplayer_names[]= {"Goose", "GRT Bus", "Tim Hortons Doughnut", "Professor", "Student", "Money", "Laptop", "Pink tie"};
        ifstream info{"playersinfo.txt"};
        string myplayer_chars {"GBDPS$LT"};
        
        
        for (int i =0; i < n; ++i) {
            string name;
            while (true) {
                cout << "Please enter your name! " << endl;
                cin >> name;
                bool ifname = true;
                for(int i = 0; i < players_name.size(); ++i) {
                    if(players_name[i] == name) {
                        ifname = false;
                    }
                }
                if(!ifname) {
                    cout << "This name has been used by another player, consider another name." << endl;
                    continue;
                }
                cout << "Are you sure to use the name " << name << " ?(y/n)" << endl;
                string makesure;
                cin >> makesure;
                
                if(makesure=="y") {
                    players_name.push_back(name);
                    break;
                }
            }
            cout << "Please select a player symbol and enter the number(from 1 to 8) of the symbol!" << endl;
            
            while(getline(info,myline)) {
                cout << myline << endl;
            }   //print the content of playersinfo.h
            
            while (true) {
                int num;
                if(!(cin>>num)) {
                    cin.clear();
                    cin.ignore();
                    valid = false;
                    cout <<"Please enter a number! " << endl;
                }
                else {
                    valid = true;
                    if((num>8)||(num<1)) {
                        cout << "Invalid player number, please enter a number from 1 to 8!" << endl;
                        valid = false;
                    }
                    if(!valid) continue;
                    
                    for ( int j = 0; j < numplayer; ++j) {
                        if (myplayer_chars[num-1] == players_char[j]) {
                            cout << "Symbol " << myplayer_names[num-1] << " has been selected!" << endl;
                            cout << "Please enter another number(from 1 to 8)!" << endl;
                            valid =false;
                        }
                    }
                    if(valid) {
                        ++numplayer;
                        players_char.push_back(myplayer_chars[num-1]);
                        
                        // players_name.push_back(myplayer_names[num-1]);
                        /*players_char[i] = myplayer_chars[num-1];
                         players_name[i] = myplayer_names[num-1];*/
                        break;
                    }
                }
                
            }
        }
        
        for(int i =0; i < n; ++i) {
            int a = i+1;
            cout << "Player #" << a << " is " << players_name[i] << ", and your character is " << players_char[i] << "." << endl;
            
        }
        
        
        //shared_ptr<Square> p = make_shared<PAC>(PAC(54,17,true,9,150,"Gym",150,nullptr));
        
        //auto pac = make_shared<PAC>(PAC(54,17,true,0,150,"Gym",150,nullptr));
        
        
        
        
        auto AL = make_shared<Academic>(Academic("AL",54,73,true,1,40,"Arts1",2,nullptr,51,73,50,10,30,90,160,250));
        auto ML = make_shared<Academic>(Academic("ML",54,57,true,3,60,"Arts1",4,nullptr,51,57,50,20,60,180,320,450));
        vector <shared_ptr<Ownable>> acd1;
        acd1.emplace_back(AL);
        acd1.emplace_back(ML);
        AL->set_monopoly_list(acd1);
        ML->set_monopoly_list(acd1);
        
        
        
        
        auto ECH = make_shared<Academic>(Academic("ECH",54,33,true,6,100,"Arts2",6,nullptr,51,33,50,30,90,270,400,550));
        auto PAS = make_shared<Academic>(Academic("PAS",54,17,true,8,100,"Arts2",6,nullptr,51,17,50,30,90,270,400,550));
        auto HH = make_shared<Academic>(Academic("HH",54,9,true,9,120,"Arts2",8,nullptr,51,9,50,40,100,300,450,600));
        vector <shared_ptr<Ownable>> acd2;
        acd2.emplace_back(ECH);
        acd2.emplace_back(PAS);
        acd2.emplace_back(HH);
        ECH->set_monopoly_list(acd2);
        PAS->set_monopoly_list(acd2);
        HH->set_monopoly_list(acd2);
        
        
        
        auto RCH = make_shared<Academic>(Academic("RCH",49,1,true,11,140,"Eng",10,nullptr,46,1,100,50,150,450,625,750));
        auto DWE = make_shared<Academic>(Academic("DWE",39,1,true,13,140,"Eng",10,nullptr,36,1,100,50,150,450,625,750));
        auto CPH = make_shared<Academic>(Academic("CPH",34,1,true,14,160,"Eng",12,nullptr,31,1,100,60,180,500,700,900));
        vector <shared_ptr<Ownable>> acd3;
        acd3.emplace_back(RCH);
        acd3.emplace_back(DWE);
        acd3.emplace_back(CPH);
        RCH->set_monopoly_list(acd3);
        DWE->set_monopoly_list(acd3);
        CPH->set_monopoly_list(acd3);
        
        
        
        auto LHI = make_shared<Academic>(Academic("LHI",24,1,true,16,180,"Health",14,nullptr,21,1,100,70,200,550,750,950));
        auto BMH = make_shared<Academic>(Academic("BMH",14,1,true,18,180,"Health",14,nullptr,11,1,100,70,200,550,750,950));
        auto OPT = make_shared<Academic>(Academic("OPT",9,1,true,19,200,"Health",16,nullptr,6,1,100,80,220,600,800,1000));
        vector <shared_ptr<Ownable>> acd4;
        acd4.emplace_back(LHI);
        acd4.emplace_back(BMH);
        acd4.emplace_back(OPT);
        LHI->set_monopoly_list(acd4);
        BMH->set_monopoly_list(acd4);
        OPT->set_monopoly_list(acd4);
        
        
        auto EV1 = make_shared<Academic>(Academic("EV1",4,9,true,21,220,"Env",18,nullptr,1,9,150,90,250,700,875,1050));
        auto EV2 = make_shared<Academic>(Academic("EV2",4,25,true,23,220,"Env",18,nullptr,1,25,150,90,250,700,875,1050));
        auto EV3 = make_shared<Academic>(Academic("EV3",4,33,true,24,240,"Env",20,nullptr,1,33,150,100,300,50,925,1100));
        vector <shared_ptr<Ownable>> acd5;
        acd5.emplace_back(EV1);
        acd5.emplace_back(EV2);
        acd5.emplace_back(EV3);
        EV1->set_monopoly_list(acd5);
        EV2->set_monopoly_list(acd5);
        EV3->set_monopoly_list(acd5);
        
        
        auto PHYS = make_shared<Academic>(Academic("PHYS",4,49,true,26,260,"Sci1",22,nullptr,1,49,150,110,330,800,975,1150));
        auto B1 = make_shared<Academic>(Academic("B1",4,57,true,27,260,"Sci1",22,nullptr,1,57,150,110,330,800,975,1150));
        auto B2 = make_shared<Academic>(Academic("B2",4,73,true,29,280,"Sci1",24,nullptr,1,73,150,120,360,850,1025,1200));
        vector <shared_ptr<Ownable>> acd6;
        acd6.emplace_back(PHYS);
        acd6.emplace_back(B1);
        acd6.emplace_back(B2);
        PHYS->set_monopoly_list(acd6);
        B1->set_monopoly_list(acd6);
        B2->set_monopoly_list(acd6);
        
        
        auto EIT= make_shared<Academic>(Academic("EIT",9,81,true,31,300,"Sci2",26,nullptr,6,81,200,130,390,900,1100,1275));
        auto ESC = make_shared<Academic>(Academic("ESC",14,81,true,32,300,"Sci2",26,nullptr,11,81,200,130,390,900,1100,1275));
        auto C2 = make_shared<Academic>(Academic("C2",24,81,true,34,320,"Sci2",28,nullptr,21,81,200,150,450,1000,1200,1400));
        vector <shared_ptr<Ownable>> acd7;
        acd7.emplace_back(EIT);
        acd7.emplace_back(ESC);
        acd7.emplace_back(C2);
        EIT->set_monopoly_list(acd7);
        ESC->set_monopoly_list(acd7);
        C2->set_monopoly_list(acd7);
        
        
        auto MC = make_shared<Academic>(Academic("MC",39,81,true,37,350,"Math",35,nullptr,36,81,200,175,500,1100,1300,1500));
        auto DC = make_shared<Academic>(Academic("DC",49,81,true,39,400,"Math",50,nullptr,46,81,200,200,600,1400,1700,2000));
        vector <shared_ptr<Ownable>> acd8;
        acd8.emplace_back(MC);
        acd8.emplace_back(DC);
        MC->set_monopoly_list(acd8);
        DC->set_monopoly_list(acd8);
        
        
        auto PAC = make_shared<Gym>(Gym("PAC",44,1,true,12,150,"Gym",0,nullptr));
        auto CIF = make_shared<Gym>(Gym("CIF",4,65,true,28,150,"Gym",0,nullptr));
        vector <shared_ptr<Ownable>> gym;
        gym.emplace_back(PAC);
        gym.emplace_back(CIF);
        PAC->set_monopoly_list(gym);
        CIF->set_monopoly_list(gym);
        
        
        
        auto MKV = make_shared<Rez>(Rez("MKV",54,41,true,5,200,"Rez",0,nullptr));
        auto UWP = make_shared<Rez>(Rez("UWP",29,1,true,15,200,"Rez",0,nullptr));
        auto V1 = make_shared<Rez>(Rez("V1",4,41,true,25,200,"Rez",0,nullptr));
        auto REV = make_shared<Rez>(Rez("REV",29,81,true,35,200,"Rez",0,nullptr));
        vector <shared_ptr<Ownable>> rez;
        rez.emplace_back(MKV);
        rez.emplace_back(UWP);
        rez.emplace_back(V1);
        rez.emplace_back(REV);
        MKV->set_monopoly_list(rez);
        UWP->set_monopoly_list(rez);
        V1->set_monopoly_list(rez);
        REV->set_monopoly_list(rez);
        
        
        
        auto OSAP = make_shared<Nonownable>(Nonownable("COLLECT OSAP",54,81,false,0));
        auto SLC1 = make_shared<SLC>(SLC("SLC",54,65,false,2));  // SLC1
        auto TUITION = make_shared<Nonownable>(Nonownable("TUITION",54,49,false,4));
        auto NH1 = make_shared<Needles>(Needles("NEEDLES HALL",54,25,false,7)); //NEEDLES HALL : NH
        auto DCT = make_shared<Nonownable>(Nonownable("DC Tims Line",54,1,false,10));//DC Tims : DCT
        auto SLC2 = make_shared<SLC>(SLC("SLC",19,1,false,17));
        auto GN = make_shared<Nonownable>(Nonownable("Goose Nesting",4,1,false,20));
        auto NH2 = make_shared<Needles>(Needles("NEEDLES HALL",4,17,false,22));
        auto GTT = make_shared<Nonownable>(Nonownable("GO TO TIMS",4,81,false,30));
        auto SLC3 = make_shared<SLC>(SLC("SLC",19,81,false,33));
        auto NH3 = make_shared<Needles>(Needles("NEEDLES HALL",34,81,false,36));
        auto CF = make_shared<Nonownable>(Nonownable("COOP FEE",44,81,false,38));
        
        
        
        
        vector <shared_ptr<Square>> squares;
        
        
        squares.emplace_back(OSAP);
        squares.emplace_back(AL);
        squares.emplace_back(SLC1);
        squares.emplace_back(ML);
        squares.emplace_back(TUITION);
        squares.emplace_back(MKV);
        squares.emplace_back(ECH);
        squares.emplace_back(NH1);
        squares.emplace_back(PAS);
        squares.emplace_back(HH);
        squares.emplace_back(DCT);
        squares.emplace_back(RCH);
        squares.emplace_back(PAC);
        squares.emplace_back(DWE);
        squares.emplace_back(CPH);
        squares.emplace_back(UWP);
        squares.emplace_back(LHI);
        squares.emplace_back(SLC2);
        squares.emplace_back(BMH);
        squares.emplace_back(OPT);
        squares.emplace_back(GN);
        squares.emplace_back(EV1);
        squares.emplace_back(NH2);
        squares.emplace_back(EV2);
        squares.emplace_back(EV3);
        squares.emplace_back(V1);
        squares.emplace_back(PHYS);
        squares.emplace_back(B1);
        squares.emplace_back(CIF);
        squares.emplace_back(B2);
        squares.emplace_back(GTT);
        squares.emplace_back(EIT);
        squares.emplace_back(ESC);
        squares.emplace_back(SLC3);
        squares.emplace_back(C2);
        squares.emplace_back(REV);
        squares.emplace_back(NH3);
        squares.emplace_back(MC);
        squares.emplace_back(CF);
        squares.emplace_back(DC);
        
        
        
        
        
        
        
        auto t = make_shared<Textdisplay>(Textdisplay(myboard));
        
        vector <shared_ptr<Player>> players;
        
        auto q = make_shared<Player>(Player(players_name[0],players_char[0],0,squares,0,squares[0],squares[0],t));
        shared_ptr <Player> myplayer = q;
        players.emplace_back(q);
        
        
        for(int i = 1; i < n; ++i) {
            auto q = make_shared<Player>(Player(players_name[i],players_char[i],i,squares,i,squares[0],squares[0],t));
            players.emplace_back(q);
        }
        
        for(int i = 0; i < n-1;++i) {
            players[i]->set_next_player(players[i+1]);
            players[i]->set_position(0,false);
        }
        players[n-1]->set_next_player(players[0]);
        players[n-1]->set_position(0,false);
        
        
        
        
        
        Gameboard mygameboard{n,4,players,myplayer,squares,t};
        auto g = make_shared<Gameboard>(Gameboard(mygameboard));
        cout << *t;
        
        
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// a new game initialization finished
        
        
        
        
        cin.exceptions(ios::eofbit|ios::failbit);
        string cmd;
        bool ifafter=false;
        bool iftrade =false;
        bool ifimprove =true;
        int r1;
        int r2;
        int r = 0;
        string player_name=myplayer->get_name();
        read_cmd(players[0], players, players_name, squares, t, g, n);
        
        
        
        
    }
}

