#include <iostream>
#include <vector>
#include "Square.h"
using namespace std;

Square::Square(string name, int row, int col, bool ownable, int square_num): name{name},row{row}, col{col}, ownable{ownable}, square_num{square_num}{}

bool Square::is_ownable() {
    return ownable;
}

int Square::get_square_num(){
    return square_num;
}

int Square::get_row(){
    return row;
}

int Square::get_col(){
    return col;
}

string Square::get_square_name(){
    return name;
}

Square::~Square() { /*cout << "!" << endl;*/}



