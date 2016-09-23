#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include "SLC.h"
using namespace std;

SLC::SLC(string name, int row, int col, bool ownable, int square_num): Chance{name,row,col,ownable,square_num}{
    s1.emplace_back("Back 3");
    s1.emplace_back("Back 2");
    s1.emplace_back("Back 1");
    s1.emplace_back("Forward 1");
    s1.emplace_back("Forward 2");
    s1.emplace_back("Forward 3");
}


string SLC::calculus(bool open){
    if(!open){
        int prob = rand() % 24;
        if(prob < 3){
            return s1[0];
        } else if(prob < 7){
            return s1[1];
        } else if(prob < 11){
            return s1[2];
        } else if(prob < 14){
            return s1[3];
        } else if(prob < 18){
            return s1[4];
        } else if(prob < 22){
            return s1[5];
        } else if(prob < 23){
            return "Go to DC Tims Line";
        } else {
            return "Advance to Collect OSAP";
        }
    } else {
        int pro = rand() % 2400;
        if(pro < 297) {
            return s1[0];
        } else if(pro < 693){
            return s1[1];
        } else if(pro < 1089){
            return s1[2];
        } else if(pro < 1389){
            return s1[3];
        } else if(pro < 1782){
            return s1[4];
        } else if(pro < 2178){
            return s1[5];
        } else if(pro < 2277){
            return "Go to DC Tims Line";
        } else if(pro < 2376){
            return "Advance to Collect OSAP";
        } else {
            return "receive a winning Roll Up the Rim cup";
        }
        
    }
}

int SLC::go_to(shared_ptr<Player> p, string cal){
    int position = p->get_cur_square()->get_square_num();
    if(cal=="Go to DC Tims Line"){
        return 10;   //bool = false
    } else if(cal == "Advance to Collect OSAP"){
        return 10;    //bool = false
    } else if(cal == "receive a winning Roll Up the Rim cup"){
        return 0;
        //Rim......
    } else if(cal == "Back 3"){
        if(position == 2){
            return 39;
        } else {
            return position-3;
        }
    } else if(cal == "Back 2"){
        return position-2;
    } else if(cal == "Back 1") {
        return position-1;
    } else if(cal == "Forward 1"){
        return position+1;
    } else if(cal == "Forward 2"){
        return position+2;
    } else {
        return position+3;
    }
}

    
    
    



//consume a player to track the player's position


















        
    
    
    
    
