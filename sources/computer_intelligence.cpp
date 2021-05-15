// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#include "computer_intelligence.h"

computer_intelligence::computer_intelligence() noexcept {
    for (auto &rows: shots) {
        std::fill(rows.begin(), rows.end(), 0);
    }

    for (auto &rows: computer_field) {
        std::fill(rows.begin(), rows.end(), symbols::sea);
    }
}

std::pair<int, int> computer_intelligence::aiming(int x, int y) {
    int direction = shot_direction(x, y);
    if (direction == 1) {
        try {
            if (shots.at(x - 1).at(y) == 0) {
                std::pair<int, int> p(x - 1, y);
                return p;
            }
        }
        catch (std::out_of_range &e) {}
        while (shots[x][y] != 0) {
            ++x;
        }
        std::pair<int, int> p(x, y);
        return p;
    }
    if (direction == 2) {
        try {
            if (shots.at(x).at(y - 1) == 0) {
                std::pair<int, int> p(x, y - 1);
                return p;
            }
        }
        catch (std::out_of_range &e) {}
        while (shots[x][y] != 0) {
            ++y;
        }
        std::pair<int, int> p(x, y);
        return p;
    }
    if (direction == 3) {
        try {
            if (shots.at(x + 1).at(y) == 0) {
                std::pair<int, int> p(x + 1, y);
                return p;
            }
        }
        catch (std::out_of_range &e) {}
        while (shots[x][y] != 0) {
            --x;
        }
        std::pair<int, int> p(x, y);
        return p;
    }
    if (direction == 4) {
        try {
            if (shots.at(x).at(y + 1) == 0) {
                std::pair<int, int> p(x, y + 1);
                return p;
            }
        }
        catch (std::out_of_range &e) {}
        while (shots[x][y] != 0) {
            --y;
        }
        std::pair<int, int> p(x, y);
        return p;
    }

    try {
        if (shots.at(x - 1).at(y) == 0) {
            std::pair<int, int> p(x - 1, y);
            return p;
        }
    }
    catch (std::out_of_range &e) {}

    try {
        if (shots.at(x).at(y - 1) == 0) {
            std::pair<int, int> p(x, y - 1);
            return p;
        }
    }
    catch (std::out_of_range &e) {}

    try {
        if (shots.at(x + 1).at(y) == 0) {
            std::pair<int, int> p(x + 1, y);
            return p;
        }
    }
    catch (std::out_of_range &e) {}

    try {
        if (shots.at(x).at(y + 1) == 0) {
            std::pair<int, int> p(x, y + 1);
            return p;
        }
    }
    catch (std::out_of_range &e) {}
}

int computer_intelligence::shot_direction(int x, int y) {
    try {
        if (shots.at(x + 1).at(y) == 1) {
            return 1;
        }
    }
    catch (std::out_of_range &e) {}
    try {
        if (shots.at(x).at(y + 1) == 1) {
            return 2;
        }
    }
    catch (std::out_of_range &e) {}
    try {
        if (shots.at(x - 1).at(y) == 1) {
            return 3;
        }
    }
    catch (std::out_of_range &e) {}
    try {
        if (shots.at(x).at(y - 1) == 1) {
            return 4;
        }
    }
    catch (std::out_of_range &e) {}
    return 0;
}

std::pair<int, int> computer_intelligence::shot() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (shots[i][j] == 1) {
                std::pair<int, int> p = aiming(i, j);
                return p;
            }
        }
    }

    int x = rand() % 10;
    int y = rand() % 10;
    while (shots[x][y] != 0) {
        x = rand() % 10;
        y = rand() % 10;
    }
    std::pair<int, int> p(x, y);
    return p;
}

std::array<std::array<int, 10>, 10> &computer_intelligence::get_shots() {
    return shots;
}

bool computer_intelligence::check_ship(const int cur_x, const int cur_y, const size_t size_ship, const bool position) {
    if (computer_field[cur_x][cur_y] == symbols::ship || computer_field[cur_x][cur_y] == symbols::empty) {
        return false;
    }
    if (!position) {
        if (10 - cur_x >= size_ship) {
            for (size_t i = 0; i < size_ship; ++i) {
                if (computer_field[cur_x + i][cur_y] == symbols::ship ||
                    computer_field[cur_x + i][cur_y] == symbols::empty) {
                    return false;
                }
            }
            return true;
        }
    } else {
        if (10 - cur_y >= size_ship) {
            for (size_t i = 0; i < size_ship; ++i) {
                if (computer_field[cur_x][cur_y + i] == symbols::ship ||
                    computer_field[cur_x][cur_y + i] == symbols::empty) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}


void computer_intelligence::create_ship(const int cur_x, const int cur_y, const size_t size_ship, const bool position) {
    if (!position) {
        for (size_t i = 0; i < size_ship; ++i) {
            computer_field[cur_x + i][cur_y] = symbols::ship;
        }
        for (size_t i = 0; i < size_ship + 2; ++i) {
            try {
                computer_field.at(cur_x + i - 1).at(cur_y + 1) = symbols::empty;
            }
            catch (std::out_of_range &e) {}

            try {
                computer_field.at(cur_x + i - 1).at(cur_y - 1) = symbols::empty;
            }
            catch (std::out_of_range &e) {}
        }
        try {
            computer_field.at(cur_x - 1).at(cur_y) = symbols::empty;
        }
        catch (std::out_of_range &e) {}
        try {
            computer_field.at(cur_x + size_ship).at(cur_y) = symbols::empty;
        }
        catch (std::out_of_range &e) {}
    } else {
        for (size_t i = 0; i < size_ship; ++i) {
            computer_field[cur_x][cur_y + i] = symbols::ship;
        }
        for (size_t i = 0; i < size_ship + 2; ++i) {
            try {
                computer_field.at(cur_x + 1).at(cur_y + i - 1) = symbols::empty;
            }
            catch (std::out_of_range &e) {}

            try {
                computer_field.at(cur_x - 1).at(cur_y + i - 1) = symbols::empty;
            }
            catch (std::out_of_range &e) {}
        }
        try {
            computer_field.at(cur_x).at(cur_y - 1) = symbols::empty;
        }
        catch (std::out_of_range &e) {}
        try {
            computer_field.at(cur_x).at(cur_y + size_ship) = symbols::empty;
        }
        catch (std::out_of_range &e) {}
    }
}


void computer_intelligence::location_ships() {
    for (size_t i = 0; i < 10; ++i) {
        int cur_x;
        int cur_y;
        bool position;
        do {
            cur_x = rand() % 10;
            cur_y = rand() % 10;
            position = rand() % 2;
        } while (!check_ship(cur_x, cur_y, ships[i], position));
        create_ship(cur_x, cur_y, ships[i], position);
    }
}


std::array<std::array<char, 10>, 10> &computer_intelligence::get_computer_field() {
    return computer_field;
}
