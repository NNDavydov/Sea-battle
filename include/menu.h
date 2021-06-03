// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#ifndef HOMEWORK_2_MENU_H
#define HOMEWORK_2_MENU_H

#include <unistd.h>
#include <string>
#include <ctime>

#include "location_ships.h"
#include "user_field.h"
#include "computer_intelligence.h"
#include "computer_field.h"


class WINDOW_MENU{
private:
    const int height = 30;
    const int width = 60;
    const int win_x = COLS / 2 - width / 2;
    const int win_y = LINES / 2 - height / 2;
    WINDOW *window_menu;
    int x = 0;

public:
    WINDOW_MENU() noexcept;

    ~WINDOW_MENU() noexcept;

    void move_up();

    void move_down();

    void display() const;

    void switch_window();

    void instructions() const;

    void game() const;
};

#endif //HOMEWORK_2_MENU_H
