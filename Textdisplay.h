#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <vector>



class Textdisplay{
    std::vector <std::vector<char>> theDisplay;
public:
    void notified_char(int row_last, int col_last, int row_now,int col_now,int position,char c);  //last_square " ", cur_square "char"
    void notified_improve(int row, int col);
    void cancel_improve(int row, int col);
    Textdisplay(std::vector <std::vector<char>> theDisplay);
    friend std::ostream &operator<< (std::ostream &out, const Textdisplay &td);
};




#endif /* textdisplay_h */

