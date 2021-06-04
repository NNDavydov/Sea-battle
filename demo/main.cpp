// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#include <ncurses.h>
#include <stdlib.h>

#include "main_menu.h"


int main() {
    if (!initscr()) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(1);
    }
    initscr();
    keypad(stdscr, true);

    WINDOW_MENU menu;
    menu.switch_window();

    endwin();
    return 0;
}

