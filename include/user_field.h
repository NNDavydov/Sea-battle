// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#ifndef HOMEWORK_2_USER_FIELD_H
#define HOMEWORK_2_USER_FIELD_H
#include <ncurses.h>
#include <cstdlib>
#include <array>
#include <string>

#include "game_symbols.h"

class WINDOW_GAME_MY_FIELD {
private:
    const int height = 23;
    const int width = 42;
    const int win_x = 5;
    const int win_y = 3;
    WINDOW *window_my_field;
    std::array<std::array<char, 10>, 10> my_field_;
public:
    explicit WINDOW_GAME_MY_FIELD(std::array<std::array<char, 10>, 10> my_field) noexcept;

    ~WINDOW_GAME_MY_FIELD();

    void display() const;

    bool computer_move(std::array<std::array<int, 10>, 10> &shots, int x, int y);

    bool is_ship_sunk(std::array<std::array<int, 10>, 10> &shots, int x, int y, std::string direction = "");

    void automatic_bombardment(std::array<std::array<int, 10>, 10> &shots, int x, int y);

    bool availability_of_ships() const;
};

#endif //HOMEWORK_2_USER_FIELD_H
