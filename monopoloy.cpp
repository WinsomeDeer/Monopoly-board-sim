#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>

// Function to calculate dice throws and keep track of number of doubles.
int dice_throw(){
    int no_doubles = 0;
    int dice1 = (std::rand() % 6), dice2 = (std::rand() % 6);
    if(dice1 == dice2){
        no_doubles++;
        if(no_doubles == 3){
            return -1;
        }
        else{
            return dice1 + dice2;
        }
    }
    else{
        return dice1 + dice2;
    }
}

// Main loop to count the squares landed on.
int main(){
    int i = 0, sq_total = 40, moves = 0;
    std::vector<int> board(sq_total, 0);
    while(i <= 10000){
        moves += dice_throw();
        // If we've gone past GO.
        if(moves % sq_total <= 40){
            
        }
    }
    return 0;
}
