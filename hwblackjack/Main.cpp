#include "Game.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "\t\tWelcome to Blackjack!\n\n";
    
    char again = 'y';
    std::string playerName;
    
    std::cout << "Enter your name: ";
    std::getline(std::cin, playerName);
    
    while (again == 'y' || again == 'Y') {
        Game game(playerName);
        game.play();
        
        std::cout << "\nDo you want to play again? (Y/N): ";
        std::cin >> again;
        std::cin.ignore(); // Clear the input buffer
    }
    
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}