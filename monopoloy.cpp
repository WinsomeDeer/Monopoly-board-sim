#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <time.h>

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
// Main loop to count the squares landed on.
int main(){
    srand(time(NULL));
    int i = 0;
    int sq_total = 40;
    int moves = 0;
    int no_of_doubles = 0;
    int move;
    int dice1, dice2;
    int community_chest_card, chance_card;
    bool GOJ = false, jailed = false;
    std::vector<int> board(sq_total, 0);
    while(i++ <= 100000){
        // Roll the dice.
        dice1 = (rand()%6)+1, dice2 = (rand()%6)+1;
        if(dice1 == dice2){
            no_of_doubles++;
            // Check if we have rolled three doubles.
            if(no_of_doubles == 3){
                moves = 10;
                jail();
            }
            else{
                moves += dice1 + dice2;
            }
        }
        // Reset doubles if needed.
        else if(dice1 != dice2 && no_of_doubles > 0){
            no_of_doubles = 0;
            moves += dice1 + dice2;
        }
        else{
            moves += dice1 + dice2;
        }
        board[moves]++;
        // If we've gone past GO.
        if(moves % sq_total <= 39){
            moves = moves % sq_total;
            board[moves]++;
        }
        // Check for community chest.
        if(moves == 2 || moves == 17 || moves == 33){
            community_chest_card = (rand()%16) + 1;
            switch(community_chest_card){
                // Advance to GO.
                case 1:
                    moves = 0;
                    break;
                // Get out of jail free card.
                case 2:
                    GOJ = true;
                    break;
                // Go to jail. 
                case 3:
                    moves = 10;
                    jail();
                    break;
            }
        board[moves]++;
        }
        // Check for chance cards.
        if(moves == 7 || moves == 22 || moves == 36){
            chance_card = (rand()%16) + 1;
            switch(chance_card){
                // Advance to GO.
                case 1:
                    moves = 0;
                    break;
                // Advance to Trafalgar square.
                case 2:
                    moves = 24;
                    break;
                // Advance to Pall Mall.
                case 3:
                    moves = 11;
                    break;
                // Advance to nearest utility.
                case 4:
                    if(moves == 22){
                        moves = 28;
                    }
                    else{
                        moves = 12;
                    }
                    break;
                // Advance to nearest station.
                case 5:
                    if(moves == 7){
                        moves = 15;
                    }
                    else if(moves == 22){
                        moves = 25;
                    }
                    else{
                        moves = 36;
                    }
                    break;
                // Get out of jail free card.
                case 6:
                    GOJ = true;
                    break;
                // Go back 3 spaces.
                case 7:
                    moves -= 3;
                    break;
                // Go to Jail.
                case 8:
                    moves = 10;
                    jail();
                    break;
                // Go to Kings Cross station.
                case 9:
                    moves = 5;
                    break;
                // Advance to Mayfair.
                case 10:
                    moves = 39;
                    break;
            }
            board[moves]++;
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
