//
//  sudoku.cpp
//  
//
//  Created by ching on 2016/3/23.
//
//

#include "Sudoku.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

/*construct*/
Sudoku::Sudoku(){
    int i;
    for(i=0;i<Sudoku::SUDOKU_SIZE;i++)
        Map[i]=0;
}

Sudoku::Sudoku(const int init_map[]){
    int i;
    for(int i=0; i<Sudoku::SUDOKU_SIZE;i++)
        Map[i] = init_map[i];
}

/*SetMap*/
void Sudoku::SetMap(const int set_map[]){
    int i;
    for(int i=0; i<Sudoku::SUDOKU_SIZE;i++)
        Map[i] = set_map[i];
}

/*setElement*/
void Sudoku::setElement(int index, int value){
        Map[index]=value;
}

/*giveQestion*/
void Sudoku::giveQuestion(){
    int i;
    int Q1[81]={5,3,0,0,7,0,0,0,0,
        6,0,0,1,9,5,0,0,0,
        0,9,8,0,0,0,0,6,0,
        8,0,0,0,6,0,0,0,3,
        4,0,0,8,0,3,0,0,1,
        7,0,0,0,2,0,0,0,6,
        0,6,0,0,0,0,2,8,0,
        0,0,0,4,1,9,0,0,5,
        0,0,0,0,8,0,0,7,9};
    for (int i = 0; i < 81; ++i) printf("%d%c", Q1[i], (i + 1) % 9 != 0 ? ' ' : '\n');
    /*for(i=0;i<81;i++){
        
        if(i%9==0)cout<<"\n";
        cout<< Q1[i] <<"\t";
        
    }*/
    
    
}


 /*readIn*/
void Sudoku::readIn(){
    int i;
    /*ifstream inFile("",ios::in);
    for(i=0;i<81;i++){
        inFile >> Map[i];
        
    }*/
    for (int i = 0; i < 81; ++i) scanf("%1d", &Map[i]);
}

/*solve*/

void Sudoku::solve(){
    Sudoku ques;
    Sudoku ans;
    for(int i=0;i<SUDOKU_SIZE;i++)
        ques.setElement(i,Map[i]);
    
    //for(int i=0;i<SUDOKU_SIZE;i++)
      //  printf("%d",ques.Map[i]);
    if(solver(ques,ans)==true)
        cout<<"1";
    else if(solver(ques,ans)==false)
        cout<<"0";
}

bool Sudoku::solver(Sudoku ques, Sudoku &ans){
    int firstZero;
    
    firstZero=getFirstZeroIndex();
  
    if(firstZero==-1){
        if(ques.isCorrect()){
            ans=ques;
            return true;
        }
        else return false;
    }
    else {
        for(int num=1; num<=9; ++num){
            ques.setElement(firstZero,num);
            
            if(!ques.isCorrect_single(firstZero)){
                continue;
                
            }
            solver(ques,ans);
            return true;
            
        }
        return false;
    }
    

}
bool Sudoku::isCorrect(){
    bool check_result;
    int check_arr[9];
    int location;
    int i,j;
    //check row
    for(i=0;i<81;i+=9){
        for(j=0;j<9;j++){
            check_arr[j]=Map[i+j];
        }
        check_result=checkUnity(check_arr);
        if(check_result==false)
            return false;
    }
    //check column
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            check_arr[j]=Map[i+j*9];
        }
        check_result=checkUnity(check_arr);
        if(check_result==false)
            return false;
    }
    //check cell
    for(int i=0; i<9; ++i){
        for(int j=0; j<9; ++j)
          {
            location = 27*(i/3) + 3*(i%3)+9*(j/3) + (j%3);
              check_arr[j] = Map[location];
          }
            check_result = checkUnity(check_arr);
    if(check_result == false)
        return false;
     }
    return true;
}
    
bool Sudoku::isCorrect_single(int firstZero ){
    bool check_result;
    int check_arr[9];
    int location;
    int i,j;
    int k=0;
    int column = firstZero%9;
    int row = floor(firstZero/9);
    
    
    //check column
    for(i=column,j=0;i<column+9*8,j<9;i+=9,j++){
            check_arr[j]=Map[i];
        }
        check_result=checkUnity(check_arr);
        if(check_result==false)
            return false;
    
    //check row
    for(i=row*9,j=0;i<row*9+8,j<9;i++,j++){
            check_arr[j]=Map[i];
        }
        check_result=checkUnity(check_arr);
        if(check_result==false)
            return false;
    
    //check cell
    for(i=0;i<3;i++){
        for( j=0; j<3; ++j)
        {
            location = 27*(row/3) + 3*floor(column/3)+9*i + (j%3);
            check_arr[k] = Map[location];
            k++;
        }
    }
    k=0;
        check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    return true;
}


bool Sudoku::checkUnity(int arr[]){
    int arr_count[9]; //index
    int i;
    for(i=0; i<9; i++)
         arr_count[i] = 0;
    for(i=0;i<9;i++)
        ++arr_count[arr[i]-1];
    
    for(i=0;i<9;i++)
        if(arr_count[i]!=1)
            return false;
    
    return true;
}
int Sudoku::getFirstZeroIndex(){ 
    int i;
    for(i=0;i<SUDOKU_SIZE;i++){
        if(Map[i]==0)
            return i;
    }
    return -1;
}
/*transform*/
void Sudoku::transform(){
    
    readIn();
    
    srand(time(NULL));//(rand() % (最大值-最小值+1) ) + 最小值
    changeNum(rand()%9+1, rand()%9+1); //Exchange number a and b in the board. (1 <= a, b <= 9)
    changeRow(rand()%3, rand()%3); //Exchange row set a and b in the board, each row set include three continuous rows. (0 <= a, b <= 2)
    //changeSingleRow(int a,int b)//0 <= a, b <= 9
    changeCol(rand()%3,rand()%3); //same as ChangeRow.(0 <= a, b <= 2)
    rotate(rand()%101); //Rotate the board 90 degrees n times in clockwise direction. (0 <= n<= 100)
    flip(rand()%2) ;//If n equals to 0, flip the board vertically. Otherwise, flip it horizontally. (0 <= n <= 1)
    printout();
}

void Sudoku::printout(){
    int i;
    for(i=0;i<SUDOKU_SIZE;i++)
        printf("%d%c",Map[i],(i+1)%9==0?'\n':' ');
}

void Sudoku::changeNum(int a,int b){
    int i;
    for(i=0;i<Sudoku::SUDOKU_SIZE;i++){
        if(Map[i]==a)Map[i]=b;
        else if(Map[i]==b)Map[i]=a;
    }
}
void Sudoku::changeRow(int a, int b){
    int i;
    int map_temp[Sudoku::SUDOKU_SIZE];
    for(i=0;i<=2;i++){
        
    }
    for(i=0;i<27;i++){
        map_temp[i+b*27]=Map[i+a*27];
        map_temp[i+a*27]=Map[i+b*27];
        Map[i+b*27]=map_temp[i+b*27];
        Map[i+a*27]=map_temp[i+a*27];
        
    }
    
}
void Sudoku::changeCol(int a,int b){
    int map_temp[Sudoku::SUDOKU_SIZE];
    int j,i;
    for(j=0;j<9;j++){
        for(i=0;i<3;i++){
            map_temp[i+3*b+j*9]=Map[i+3*a+j*9];
            map_temp[i+3*a+j*9]=Map[i+3*b+j*9];
            Map[i+3*b+j*9]=map_temp[i+3*b+j*9];
            Map[i+3*a+j*9]=map_temp[i+3*a+j*9];
        }
    }
    
}
void Sudoku::rotate(int n){
    int i,j;
    int map_temp[Sudoku::SUDOKU_SIZE];
    if(n%4==1){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                map_temp[(8-i)+9*j]=Map[i*9+j];
            }
        }
        for(i=0;i<Sudoku::SUDOKU_SIZE;i++){
            Map[i]=map_temp[i];
        }
        
    }
    else if(n%4==2){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                map_temp[9*(8-i)+(8-j)]=Map[i*9+j];
            }
        }
        for(i=0;i<SUDOKU_SIZE;i++){
            Map[i]=map_temp[i];
        }
        
    }
    else if(n%4==3){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                map_temp[i+9*(8-j)]=Map[i*9+j];
            }
        }
        for(i=0;i<SUDOKU_SIZE;i++){
            Map[i]=map_temp[i];
        }
    }
    
}
void Sudoku::flip(int n){
    int i,j;
    int map_temp[SUDOKU_SIZE];
    if(n==0){//vertically
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                map_temp[9*(8-j)+i]=Map[9*j+i];
            }
        }
        for(i=0;i<SUDOKU_SIZE;i++)
            Map[i]=map_temp[i];
    }
    else if(n==1){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                map_temp[(8-j)+i*9]=Map[j+i*9];
            }
        }
        for(i=0;i<SUDOKU_SIZE;i++)
            Map[i]=map_temp[i];
    }
}
