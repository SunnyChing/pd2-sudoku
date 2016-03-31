//
//  solve.cpp
//  
//
//  Created by ching on 2016/3/24.
//
//

#include "Sudoku.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main (){
    Sudoku ss;
    ss.readIn();
    ss.solve();
    return 0;
}