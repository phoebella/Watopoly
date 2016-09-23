#include <iostream>
#include <vector>
#include "Textdisplay.h"
using namespace std;

Textdisplay::Textdisplay(vector <vector<char>> theDisplay):
theDisplay{theDisplay}{
    
}

void Textdisplay::notified_char(int row_last, int col_last, int row_now,int col_now,int position,char c){
    theDisplay[row_last][col_last+position] = ' ';
    theDisplay[row_now][col_now+position] = c;
}

void Textdisplay::notified_improve(int row, int col){
 
    theDisplay[row][col]='I';

}

void Textdisplay::cancel_improve(int row, int col){
    theDisplay[row][col]=' ';
}

ostream &operator<<(ostream &out, const Textdisplay &td){
    for(int i = 0;i<td.theDisplay.size();++i){
        for(int j = 0; j<td.theDisplay[i].size();++j){
            out << td.theDisplay[i][j];
        }
        cout << endl;
    }
    return out;
}

