// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#ifndef HOMEWORK_2_COMPUTER_FIELD_H
#define HOMEWORK_2_COMPUTER_FIELD_H

#include <ncurses.h>
#include <cstdlib>
#include <array>
#include <string>

#include "game_symbols.h"

class WINDOW_GAME_COMPUTER_FIELD{
private:
    const int height = 23;
    const int width = 42;
    const int win_x = 3;
    const int win_y = 50;
    WINDOW *window_computer_field;
    std::array<std::array<char, 10>, 10> computer_field_;
    std::array<std::array<char, 10>, 10> visible_computer_field_;
    int cur_x = 0;
    int cur_y = 0;
public:
    explicit WINDOW_GAME_COMPUTER_FIELD( std::array<std::array<char, 10>, 10>& computer_field) noexcept;

    ~WINDOW_GAME_COMPUTER_FIELD();

    void display() const;

    void interface();

    bool availability_of_ships() const;

private:
    void move_up();

    void move_down();

    void move_left();

    void move_right();

    bool ability_move(int x, int y);

    bool user_move(int x, int y);

    bool is_ship_sunk(int x, int y, std::string direction = "");

    void automatic_bombardment();

};

#endif //HOMEWORK_2_COMPUTER_FIELD_H
