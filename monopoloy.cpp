#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <unordered_map>

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
            no_doubles = 0;
            return dice1 + dice2;
        }
    }
    else{
        return dice1 + dice2;
    }
}

// Community chest function.
int community_chest(){
    int card = (rand() % 17) + 1;
    std::unordered_map<int, int> mp = {{1,0}, {5,-1}, {6,10}};
    if(mp.find(card) != mp.end()){
        return mp[card];
    }
    else{
        return 0;
    }
}

// Chance card functions
int chance_card(){
    int card = (rand() % 17) + 1;
    std::unordered_map<int, int> mp
        = {{1,0},{2,13},{3,39},{4,11},{5,}};
    if(mp.find(card) != mp.end()){
        return mp[card];
    }
    else{
        return 0;
    }
}

// Main loop to count the squares landed on.
int main(){
    int i = 0, sq_total = 40, moves = 0;
    bool GOJ = false, jailed = false;
    std::vector<int> board(sq_total, 0);
    while(i <= 10000){
        moves += dice_throw();
        // If we've gone past GO.
        if(moves % sq_total <= 40){
            moves = moves % sq_total;
        }
        // Check for community chest.
        if(moves == 2 or moves == 17 or moves == 33){
            // Get out of jail free card.
            if(community_chest() == -1){
                GOJ = true;
            }
            // Community chest cards that move you to different square.
            else if(community_chest() != 0){
                moves = community_chest();
            }
        }
        if(moves == 30){
            moves = 10;
            
        }

    }
    return 0;
}
