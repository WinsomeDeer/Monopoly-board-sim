#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <time.h>

// Function to calculate dice throws and keep track of number of doubles.
int dice_throw(int& no_doubles){
    int dice1 = (std::rand() % 6 + 1), dice2 = (std::rand() % 6 + 1);
    if(dice1 == dice2){
        no_doubles++;
        if(no_doubles == 3){
            return -1;
        }
        else{
            no_doubles = 0;
            return dice1 + dice2;
        }
    }
    else{
        return dice1 + dice2;
    }
}

// Jail Function.
int jail(){
    for(int i = 0; i < 3; i++){
        int dice1 = (std::rand() % 6 + 1), dice2 = (std::rand() % 6 + 1);
        if(dice1 == dice2){
            return dice1 + dice2;
        }
    }
    return 0;
}

// Community chest function.
int community_chest(){
    int card = (rand() % 16) + 1;
    std::unordered_map<int, int> mp = {{1,0}, {5,-1}, {6,10}};
    if(mp.find(card) != mp.end()){
        return mp[card];
    }
    else{
        return 0;
    }
}

// Chance card function.
int chance_card(int& moves){
    int card = (rand() % 16) + 1;
    std::unordered_map<int, int> mp
        = {{1,0},{2,24},{3,39},{4,11},{5, std::min({abs(5-moves), abs(15-moves), abs(25-moves), abs(35-moves)})},
            {6,std::min({abs(12-moves), abs(28-moves)})}, {8,-1}, {9, moves-3}, {10, 10}, {13,5}, {14, 0}};
    if(mp.find(card) != mp.end()){
        return mp[card];
    }
    else{
        return 0;
    }
}

// Main loop to count the squares landed on.
int main(){
    srand(time(NULL));
    int i = 0, sq_total = 40, moves = 0, no_of_doubles = 0, move;
    bool GOJ = false, jailed = false;
    std::vector<int> board(sq_total, 0);
    while(i++ <= 10000){
        move = dice_throw(no_of_doubles);
        // Check if we have rolled three doubles.
        if(move == -1){
            moves = 10;
            jail();
        }
        else{
            moves += move;
        }
        board[moves]++;
        // If we've gone past GO.
        if(moves % sq_total <= 40){
            moves = moves % sq_total;
            board[moves]++;
        }
        // Check for community chest.
        if(moves == 2 || moves == 17 || moves == 33){
            // Get out of jail free card.
            board[moves]++;
            if(community_chest() == -1){
                GOJ = true;
            }
            // Community chest cards that move you to different square.
            else if(community_chest() != 0){
                moves = community_chest();
                board[moves]++;
            }
        }
        // Check for chance cards.
        if(moves == 7 || moves == 22){
            board[moves]++;
            if(chance_card(moves) == -1){
                GOJ = true;
            }
            else{
                moves = chance_card(moves);
                board[moves]++;
            }
        }
        // If you land on 'Go to Jail'.
        if(moves == 30){
            board[moves]++;
            if(GOJ){
                GOJ = false;
            }
            else{
                jail();
            }
            moves = 10;
            board[moves]++;
        }
    }
    // For loop to display results in console.
    for(int i = 0; i < board.size(); i++){
        std::cout << i << " : " << board[i] << std::endl;
    }
    return 0;
}
