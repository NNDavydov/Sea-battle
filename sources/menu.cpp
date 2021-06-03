// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#include "menu.h"

WINDOW_MENU::WINDOW_MENU() noexcept: window_menu(newwin(height, width, win_x, win_y)) {}


WINDOW_MENU::~WINDOW_MENU() noexcept {
    delwin(window_menu);
}


void WINDOW_MENU::move_up() {
    if(x != 2) ++x;
}


void WINDOW_MENU::move_down() {
    if(x != 0) --x;
}


void WINDOW_MENU::switch_window(){
    if (!initscr()) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(1);
    }
    initscr();
    noecho();
    keypad(stdscr, true);

    while(true){
        //display();
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                move_up();
                break;
            case KEY_DOWN:
                move_down();
                break;
            case KEY_F(1):
                if (x == 0) {
                    game();
                    return;
                }
                if(x == 1){
                    instructions();
                    break;
                }
                if(x == 2){
                    return;
                }
            default:
                break;
        }
    }

    endwin();
}


void WINDOW_MENU::display() const{
    refresh();
    box(window_menu, 0, 0);
    std::array<std::string, 3> string_menu = {"GAME",
                                              "INSTRUCTIONS",
                                              "EXIT"};

    for(size_t i = 0; i < string_menu.size(); ++i){
        if(i == x){
            start_color();
            init_pair(40, COLOR_WHITE, COLOR_BLACK);
            wattron(window_menu, COLOR_PAIR(40));
            mvaddstr(LINES / 2 + i * 2, COLS / 2 - string_menu[i].length() / 2, string_menu[i].data());
            wattroff(window_menu, COLOR_PAIR(40));
            use_default_colors();
        }
        else{
            mvaddstr( LINES / 2 + i * 2, COLS / 2 - string_menu[i].length() / 2, string_menu[i].data());
        }
    }
}


void WINDOW_MENU::instructions() const {
    WINDOW *win_instruction = newwin(height, width, win_x, win_y);
    mvwprintw(win_instruction, 1, 1, "--------------------------------------HELP-------------------------------------");
    mvwprintw(win_instruction, 2, 1, "There are two fields in the game:");
    mvwprintw(win_instruction, 3, 1, "the left one is the user field, the right one is the computer");
    mvwprintw(win_instruction, 4, 1, "There are also 4 types of ships in the game:");
    mvwprintw(win_instruction, 5, 1, "1 - XXXX");
    mvwprintw(win_instruction, 6, 1, "2 - XXX");
    mvwprintw(win_instruction, 7, 1, "3 - XX");
    mvwprintw(win_instruction, 8, 1, "4 - X");
    mvwprintw(win_instruction, 9, 1,
              "------------------------------------SYMBOLS-------------------------------------");
    mvwprintw(win_instruction, 10, 1, "~ - sea");
    mvwprintw(win_instruction, 11, 1, "P - ship");
    mvwprintw(win_instruction, 12, 1, "X - injured ship");
    mvwprintw(win_instruction, 13, 1, "Q - empty, cage in which no ship can be placed");
    mvwprintw(win_instruction, 13, 1, "O - miss");
    getch();
    delwin(win_instruction);
}


void WINDOW_MENU::game() const {
    srand(time(nullptr));

    noecho();
    keypad(stdscr, true);

    WINDOW_LOCATION_SHIPS w1;
    computer_intelligence AI;
    if (w1.location()) {
        AI.location_ships();
        WINDOW_GAME_MY_FIELD w2(w1.get_my_field());
        WINDOW_GAME_COMPUTER_FIELD w3(AI.get_computer_field());
        w2.display();
        w3.display();
        while (w2.availability_of_ships() && w3.availability_of_ships()) {
            w3.interface();
            while (true) {
                std::pair<int, int> p = AI.shot();
                usleep(1000000);
                w2.computer_move(AI.get_shots(), p.first, p.second);
                if (!w2.is_hit(p.first, p.second)) break;;
            }
        }
    }
}

