// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#ifndef SEMESTER2_HOMEWORK_2_COMPUTER_INTELLIGENCE_H
#define SEMESTER2_HOMEWORK_2_COMPUTER_INTELLIGENCE_H

#include <array>

#include "game_symbols.h"

class computer_intelligence {
private:
    std::array<std::array<int, 10>, 10> shots;
    std::array<std::array<char, 10>, 10> computer_field;
    size_t ships[10] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
public:
    computer_intelligence() noexcept;

    std::pair<int, int> shot();

    std::array<std::array<int, 10>, 10> &get_shots();

    std::array<std::array<char, 10>, 10> &get_computer_field();

    void location_ships();

    ~computer_intelligence() noexcept = default;

private:
    std::pair<int, int> aiming(int x, int y);

    int shot_direction(int x, int y);

    bool check_ship(int cur_x, int cur_y, size_t size_ship, bool position);

    void create_ship(int cur_x, int cur_y, size_t size_ship, bool position);
};

#endif //SEMESTER2_HOMEWORK_2_COMPUTER_INTELLIGENCE_H
