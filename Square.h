#ifndef _Square_h
#define _Square_h
#include <string>

class Square {
protected:
    int row;
    int col;
    bool ownable;
    int square_num;
    std::string name;
public:
    Square(std::string name,int row, int col, bool ownable, int square_num);
    bool is_ownable();
    int get_square_num();
    int get_row();
    int get_col();
    std::string get_square_name();
    virtual ~Square()=0;
};


#endif


