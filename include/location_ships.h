// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#ifndef HOMEWORK_2_LOCATION_SHIPS_H
#define HOMEWORK_2_LOCATION_SHIPS_H

#include <ncurses.h>
#include <cstdlib>
#include <array>

#include "game_symbols.h"

class WINDOW_LOCATION_SHIPS {
private:
    const int height = 23;
    const int width = 42;
    const int win_x = COLS / 2 - width / 2;
    const int win_y = LINES / 2 - height / 2;
    WINDOW *window_location_ships;
    std::array<std::array<char, 10>, 10> my_field;
    size_t ships[10] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    int cur_x = 0;
    int cur_y = 0;

public:
    WINDOW_LOCATION_SHIPS() noexcept;

    ~WINDOW_LOCATION_SHIPS();

    void display() const;

    bool location();

    std::array<std::array<char, 10>, 10> get_my_field() const;

private:
    bool check_ship(size_t size_ship, bool position);

    void move_up();

    void move_down();

    void move_left();

    void move_right();

    void create_ship(size_t size_ship, bool position);
};

#endif //HOMEWORK_2_LOCATION_SHIPS_H
