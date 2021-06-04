// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#include "main_menu.h"

WINDOW_MENU::WINDOW_MENU() noexcept: window_menu(newwin(height, width, win_y, win_x)) {}


WINDOW_MENU::~WINDOW_MENU() noexcept {
    delwin(window_menu);
}


void WINDOW_MENU::move_up() {
    if (x != 0) --x;
}


void WINDOW_MENU::move_down() {
    if (x != 2) ++x;
}


void WINDOW_MENU::display() const {
    refresh();
    box(window_menu, 0, 0);

    for (size_t i = 0; i < string_menu.size(); ++i) {
        if (i == x) {
            start_color();
            init_pair(40, COLOR_WHITE, COLOR_BLACK);
            wattron(window_menu, COLOR_PAIR(40));
            mvwprintw(window_menu, height / 2 + i * 2, width / 2 - string_menu[i].length() / 2, string_menu[i].data());
            wattroff(window_menu, COLOR_PAIR(40));
            use_default_colors();
        } else {
            mvwprintw(window_menu, height / 2 + i * 2, width / 2 - string_menu[i].length() / 2, string_menu[i].data());
        }
    }

    wrefresh(window_menu);
}


void WINDOW_MENU::switch_window() {
    display();
    getch();
    while (true) {
        display();
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
                    break;
                }
                if (x == 1) {
                    instructions();
                    break;
                }
                if (x == 2) {
                    return;
                }
            case KEY_F(3):
                return;
            default:
                break;
        }
    }
}


void WINDOW_MENU::instructions() const {
    clear();
    initscr();

    const size_t height_instructions = 24;
    const size_t width_instructions = 82;
    const int x_ = 10;
    const int y_ = 50;

    WINDOW *win_instruction = newwin(height_instructions, width_instructions, x_, y_);
    refresh();
    box(win_instruction, 0, 0);
    mvwprintw(win_instruction, 1, 1,
              "---------------------------------------HELP-------------------------------------");
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
    mvwprintw(win_instruction, 14, 1, "O - miss");
    mvwprintw(win_instruction, 15, 1,
              "-------------------------------------KEYS--------------------------------------");
    mvwprintw(win_instruction, 16, 1, "f1 - shot");
    mvwprintw(win_instruction, 17, 1, "f2 - change the position of the ship");
    mvwprintw(win_instruction, 18, 1, "f3 - exit");
    mvwprintw(win_instruction, 20, 1, "Copyright 2021 Davydov Nikolay davy.nikola@gmail.com");
    wrefresh(win_instruction);
    getch();
    delwin(win_instruction);

    endwin();
    clear();
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
            if (!w3.availability_of_ships()) {
                break;
            }
            while (true) {
                std::pair<int, int> p = AI.shot();
                usleep(1000000);
                w2.computer_move(AI.get_shots(), p.first, p.second);
                if (!w2.is_hit(p.first, p.second)) break;
                if (!w2.availability_of_ships()) {
                    break;
                }
            }
        }
    }
    clear();
}

