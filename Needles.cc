#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Needles.h"
#include "Player.h"
using namespace std;

Needles::Needles(string name, int row, int col, bool ownable, int square_num): Chance{name,row,col,ownable,square_num}{
    s1.emplace_back("lose 200");
    s1.emplace_back("lose 100");
    s1.emplace_back("lose 50");
    s1.emplace_back("receive 25");
    s1.emplace_back("receive 50");
    s1.emplace_back("receive 100");
    s1.emplace_back("receive 200");
}

string Needles::calculus(bool open){
    if(!open){
        int prob = rand() % 18;
        if(prob < 1){
            return s1[0];
        } else if(prob < 3){
            return s1[1];
        } else if(prob < 6){
            return s1[2];
        } else if(prob < 12){
            return s1[3];
        } else if(prob < 15){
            return s1[4];
        } else if(prob < 17){
            return s1[5];
        } else {
            return s1[6];
        }
    } else {
        int pro = rand() % 1800;
        if(pro < 99){
            return s1[0];
        } else if(pro < 297){
            return s1[1];
        } else if(pro < 594){
            return s1[2];
        } else if(pro < 1188){
            return s1[3];
        } else if(pro < 1485){
            return s1[4];
        } else if(pro < 1683){
            return s1[5];
        } else if(pro < 1782){
            return s1[6];
        } else {
            return "receive a winning Roll Up the Rim cup";
        }
    }
}


void Needles::mutate_money(shared_ptr<Player> p, string m){
    if(m=="lose 200"){
        p->set_money(-200);
    } else if(m=="lose 100"){
        p->set_money(-100);
    } else if(m=="lose 50"){
        p->set_money(-50);
    } else if(m=="receive 25"){
        p->set_money(25);
    } else if(m=="receive 50"){
        p->set_money(50);
    } else if(m=="receive 100"){
        p->set_money(100);
    } else if(m=="receive 200"){
        p->set_money(200);
    }

}



        
        
        
        
        
        
        
        
        
        
        
    
