// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com
#include "user_field.h"

WINDOW_GAME_MY_FIELD::WINDOW_GAME_MY_FIELD(const std::array<std::array<char, 10>, 10> my_field) noexcept:
        window_my_field(newwin(height, width, win_x, win_y)), my_field_(my_field) {
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            if (my_field_[i][j] == symbols::empty) {
                my_field_[i][j] = symbols::sea;
            }
        }
    }
}


WINDOW_GAME_MY_FIELD::~WINDOW_GAME_MY_FIELD() {
    delwin(window_my_field);
}


void WINDOW_GAME_MY_FIELD::display() const {
    refresh();
    box(window_my_field, 0, 0);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            start_color();
            if (my_field_[i][j] == symbols::ship) {
                init_pair(21, COLOR_GREEN, COLOR_BLACK);
                wattron(window_my_field, COLOR_PAIR(21));
                mvwprintw(window_my_field, 2 * i + 2, 4 * j + 2, "%c", my_field_[i][j]);
                wattroff(window_my_field, COLOR_PAIR(21));
            } else if (my_field_[i][j] == symbols::injured_ship) {
                init_pair(22, COLOR_RED, COLOR_BLACK);
                wattron(window_my_field, COLOR_PAIR(22));
                mvwprintw(window_my_field, 2 * i + 2, 4 * j + 2, "%c", my_field_[i][j]);
                wattroff(window_my_field, COLOR_PAIR(22));
            } else if (my_field_[i][j] == symbols::sea) {
                init_pair(23, COLOR_BLUE, COLOR_BLACK);
                wattron(window_my_field, COLOR_PAIR(23));
                mvwprintw(window_my_field, 2 * i + 2, 4 * j + 2, "%c", my_field_[i][j]);
                wattroff(window_my_field, COLOR_PAIR(23));
            } else if (my_field_[i][j] == symbols::miss) {
                init_pair(24, COLOR_YELLOW, COLOR_BLACK);
                wattron(window_my_field, COLOR_PAIR(24));
                mvwprintw(window_my_field, 2 * i + 2, 4 * j + 2, "%c", my_field_[i][j]);
                wattroff(window_my_field, COLOR_PAIR(24));
            }
            use_default_colors();
        }
    }
    wrefresh(window_my_field);
}


void WINDOW_GAME_MY_FIELD::computer_move(std::array<std::array<int, 10>, 10> &shots, const int x, const int y) {
    if (my_field_[x][y] == symbols::ship) {
        my_field_[x][y] = symbols::injured_ship;
        if (is_ship_sunk(shots, x, y)) {
            shots[x][y] = 2;
            automatic_bombardment(shots, x, y);
            display();
            return;
        }
        shots[x][y] = 1;
        display();
        return;
    }
    my_field_[x][y] = symbols::miss;
    shots[x][y] = -1;
    display();
}


bool WINDOW_GAME_MY_FIELD::is_ship_sunk(std::array<std::array<int, 10>, 10> &shots, const int x, const int y,
                                        const std::string direction) {
    try {
        if (my_field_.at(x + 1)[y] == symbols::ship) {
            return false;
        }
    }
    catch (std::out_of_range &e) {}
    try {
        if (my_field_.at(x - 1)[y] == symbols::ship) {
            return false;
        }
    }
    catch (std::out_of_range &e) {}
    try {
        if (my_field_[x].at(y + 1) == symbols::ship) {
            return false;
        }
    }
    catch (std::out_of_range &e) {}
    try {
        if (my_field_[x].at(y - 1) == symbols::ship) {
            return false;
        }
    }
    catch (std::out_of_range &e) {}


    if (direction == "") {
        try {
            if (my_field_.at(x + 1)[y] == symbols::injured_ship) {
                if (!is_ship_sunk(shots, x + 1, y, "right")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
        try {
            if (my_field_.at(x - 1)[y] == symbols::injured_ship) {
                if (!is_ship_sunk(shots, x - 1, y, "left")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
        try {
            if (my_field_[x].at(y + 1) == symbols::injured_ship) {
                if (!is_ship_sunk(shots, x, y + 1, "down")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
        try {
            if (my_field_[x].at(y - 1) == symbols::injured_ship) {
                if (!is_ship_sunk(shots, x, y - 1, "up")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
    } else if (direction == "right") {
        try {
            if (my_field_.at(x + 1)[y] == symbols::injured_ship) {
                if (!is_ship_sunk(shots, x + 1, y, "right")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
    } else if (direction == "left") {
        try {
            if (my_field_.at(x - 1)[y] == symbols::injured_ship) {
                if (!is_ship_sunk(shots, x - 1, y, "left")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
    } else if (direction == "down") {
        try {
            if (my_field_[x].at(y + 1) == symbols::injured_ship) {
                if (!is_ship_sunk(shots, x, y + 1, "down")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
    } else if (direction == "up") {
        try {
            if (my_field_[x].at(y - 1) == symbols::injured_ship) {
                if (!is_ship_sunk(shots, x, y - 1, "up")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
    }
    return true;
}


void WINDOW_GAME_MY_FIELD::automatic_bombardment(std::array<std::array<int, 10>, 10> &shots, const int x, const int y) {
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            try {
                if (my_field_.at(x + i).at(y + j) == symbols::sea) {
                    my_field_[x + i][y + j] = symbols::miss;
                    shots[x + i][y + j] = -1;
                }
            }
            catch (std::out_of_range &e) {}
        }
    }
    try {
        if (shots.at(x + 1).at(y) == 1) {
            shots[x + 1][y] = 2;
            automatic_bombardment(shots, x + 1, y);
        }
    }
    catch (std::out_of_range &e) {}
    try {
        if (shots.at(x - 1).at(y) == 1) {
            shots[x - 1][y] = 2;
            automatic_bombardment(shots, x - 1, y);
        }
    }
    catch (std::out_of_range &e) {}
    try {
        if (shots.at(x).at(y + 1) == 1) {
            shots[x][y + 1] = 2;
            automatic_bombardment(shots, x, y + 1);
        }
    }
    catch (std::out_of_range &e) {}
    try {
        if (shots.at(x).at(y - 1) == 1) {
            shots[x][y - 1] = 2;
            automatic_bombardment(shots, x, y - 1);
        }
    }
    catch (std::out_of_range &e) {}
}


bool WINDOW_GAME_MY_FIELD::availability_of_ships() const {
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            if (my_field_[i][j] == symbols::ship) {
                return true;
            }
        }
    }
    return false;
}


bool WINDOW_GAME_MY_FIELD::is_hit(int x, int y) {
    return my_field_[x][y] == symbols::injured_ship;
}
