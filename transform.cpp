//
//  transform.cpp
//  
//
//  Created by ching on 2016/3/24.
//
//

#include "Sudoku.h"
#include<iostream>

using namespace std;
int main(){
    Sudoku ss;
    ss.readIn();
    //ss.transform();
    cout<< ss.isCorrect();
    //ss.printout();
    return 0;
}
