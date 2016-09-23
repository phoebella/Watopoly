#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Nonownable.h"

using namespace std;


Nonownable::Nonownable(string name, int row, int col, bool ownable, int square_num): Square{name, row,col,ownable,square_num} {}

Nonownable::~Nonownable() {}
