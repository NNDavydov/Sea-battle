// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#include <unistd.h>

#include "location_ships.h"
#include "user_field.h"
#include "computer_intelligence.h"


int main() {
    if (!initscr()) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(1);
    }
    initscr();
    keypad(stdscr, true);
    WINDOW_LOCATION_SHIPS w;
    computer_intelligence AI;
    if (w.location()) {
        AI.location_ships();
        WINDOW_GAME_MY_FIELD w2(AI.get_computer_field());
        getch();
        while (w2.availability_of_ships()) {
            std::pair p = AI.shot();
            w2.computer_move(AI.get_shots(), p.first, p.second);
            usleep(2000000);
        }
    }
    endwin();
    return 0;
}

