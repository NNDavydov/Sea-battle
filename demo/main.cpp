// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#include <unistd.h>
#include <ctime>

#include "location_ships.h"
#include "user_field.h"
#include "computer_intelligence.h"
#include "computer_field.h"


int main() {
    if (!initscr()) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(1);
    }
    srand(time(nullptr));

    initscr();
    noecho();
    keypad(stdscr, true);

    WINDOW_LOCATION_SHIPS w1;
    computer_intelligence AI;
    if(w1.location()){
        AI.location_ships();
        WINDOW_GAME_MY_FIELD w2(w1.get_my_field());
        WINDOW_GAME_COMPUTER_FIELD w3(AI.get_computer_field());
        w2.display();
        w3.interface();
        while (w2.availability_of_ships() && w3.availability_of_ships()){
            w3.interface();
            while(true){
                std::pair<int, int> p = AI.shot();
                usleep(2000000);
                w2.computer_move(AI.get_shots(), p.first, p.second);
                if(!w2.is_hit(p.first, p.second)) break;;
            }
        }
    }
    endwin();
    return 0;
}

