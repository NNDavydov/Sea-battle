// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#include "location_ships.h"

WINDOW_LOCATION_SHIPS::WINDOW_LOCATION_SHIPS() noexcept: window_location_ships(newwin(height, width, win_y, win_x)) {
    for (auto &row: my_field) {
        std::fill(row.begin(), row.end(), symbols::sea);
    }
}

WINDOW_LOCATION_SHIPS::~WINDOW_LOCATION_SHIPS() {
    delwin(window_location_ships);
}

bool WINDOW_LOCATION_SHIPS::check_ship(const size_t size_ship, const bool position) {
    if (my_field[cur_x][cur_y] == symbols::ship || my_field[cur_x][cur_y] == symbols::empty) {
        return false;
    }
    if (!position) {
        if (10 - cur_x >= size_ship) {
            for (size_t i = 0; i < size_ship; ++i) {
                if (my_field[cur_x + i][cur_y] == symbols::ship || my_field[cur_x + i][cur_y] == symbols::empty) {
                    return false;
                }
            }
            return true;
        }
    } else {
        if (10 - cur_y >= size_ship) {
            for (size_t i = 0; i < size_ship; ++i) {
                if (my_field[cur_x][cur_y + i] == symbols::ship || my_field[cur_x][cur_y + i] == symbols::empty) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

void WINDOW_LOCATION_SHIPS::move_up() {
    if (cur_x != 0) --cur_x;
}

void WINDOW_LOCATION_SHIPS::move_down() {
    if (cur_x != 9) ++cur_x;
}

void WINDOW_LOCATION_SHIPS::move_left() {
    if (cur_y != 0) --cur_y;
}

void WINDOW_LOCATION_SHIPS::move_right() {
    if (cur_y != 9)++cur_y;
}

void WINDOW_LOCATION_SHIPS::create_ship(const size_t size_ship, bool position) {
    if (!position) {
        for (size_t i = 0; i < size_ship; ++i) {
            my_field[cur_x + i][cur_y] = symbols::ship;
        }
        for (size_t i = 0; i < size_ship + 2; ++i) {
            try {
                my_field.at(cur_x + i - 1).at(cur_y + 1) = symbols::empty;
            }
            catch (std::out_of_range &e) {}

            try {
                my_field.at(cur_x + i - 1).at(cur_y - 1) = symbols::empty;
            }
            catch (std::out_of_range &e) {}
        }
        try {
            my_field.at(cur_x - 1).at(cur_y) = symbols::empty;
        }
        catch (std::out_of_range &e) {}
        try {
            my_field.at(cur_x + size_ship).at(cur_y) = symbols::empty;
        }
        catch (std::out_of_range &e) {}
    } else {
        for (size_t i = 0; i < size_ship; ++i) {
            my_field[cur_x][cur_y + i] = symbols::ship;
        }
        for (size_t i = 0; i < size_ship + 2; ++i) {
            try {
                my_field.at(cur_x + 1).at(cur_y + i - 1) = symbols::empty;
            }
            catch (std::out_of_range &e) {}

            try {
                my_field.at(cur_x - 1).at(cur_y + i - 1) = symbols::empty;
            }
            catch (std::out_of_range &e) {}
        }
        try {
            my_field.at(cur_x).at(cur_y - 1) = symbols::empty;
        }
        catch (std::out_of_range &e) {}
        try {
            my_field.at(cur_x).at(cur_y + size_ship) = symbols::empty;
        }
        catch (std::out_of_range &e) {}
    }
}

void WINDOW_LOCATION_SHIPS::display() const {
    refresh();
    box(window_location_ships, 0, 0);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == cur_x && j == cur_y) {
                start_color();
                init_pair(1, COLOR_BLUE, COLOR_BLACK);
                wattron(window_location_ships, COLOR_PAIR(1));
                mvwprintw(window_location_ships, 2 * i + 2, 4 * j + 2, "%c", my_field[i][j]);
                wattroff(window_location_ships, COLOR_PAIR(1));
                use_default_colors();
            } else {
                mvwprintw(window_location_ships, 2 * i + 2, 4 * j + 2, "%c", my_field[i][j]);
            }
        }
    }
    wrefresh(window_location_ships);
}

bool WINDOW_LOCATION_SHIPS::location() {
    bool position = true;
    for (size_t i = 0; i < 10;) {
        clear();
        display();
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                move_up();
                break;
            case KEY_DOWN:
                move_down();
                break;
            case KEY_LEFT:
                move_left();
                break;
            case KEY_RIGHT:
                move_right();
                break;
            case KEY_F(1):
                if (check_ship(ships[i], position)) {
                    create_ship(ships[i], position);
                    ++i;
                }
                break;
            case KEY_F(2):
                position = !position;
                break;
            case KEY_F(3):
                clear();
                return false;
            default:
                break;
        }
    }
    clear();
    return true;
}

std::array<std::array<char, 10>, 10> WINDOW_LOCATION_SHIPS::get_my_field() const {
    return my_field;
}

