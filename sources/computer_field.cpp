#include "computer_field.h"

WINDOW_GAME_COMPUTER_FIELD::WINDOW_GAME_COMPUTER_FIELD(std::array<std::array<char, 10>, 10> &computer_field) noexcept:
        window_computer_field(newwin(height, width, win_x, win_y)), computer_field_(computer_field) {
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            if (computer_field_[i][j] == symbols::empty) {
                computer_field_[i][j] = symbols::sea;
            }
        }
    }

    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            visible_computer_field_[i][j] = symbols::sea;
        }
    }
}

WINDOW_GAME_COMPUTER_FIELD::~WINDOW_GAME_COMPUTER_FIELD() {
    delwin(window_computer_field);
}

void WINDOW_GAME_COMPUTER_FIELD::display() const {
    refresh();
    box(window_computer_field, 0, 0);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            start_color();
            if (cur_x == i && cur_y == j) {
                init_pair(30, COLOR_WHITE, COLOR_BLACK);
                wattron(window_computer_field, COLOR_PAIR(30));
                mvwprintw(window_computer_field, 2 * i + 2, 4 * j + 2, "%c", visible_computer_field_[i][j]);
                wattroff(window_computer_field, COLOR_PAIR(30));
            } else if (visible_computer_field_[i][j] == symbols::sea) {
                init_pair(33, COLOR_BLUE, COLOR_BLACK);
                wattron(window_computer_field, COLOR_PAIR(33));
                mvwprintw(window_computer_field, 2 * i + 2, 4 * j + 2, "%c", visible_computer_field_[i][j]);
                wattroff(window_computer_field, COLOR_PAIR(33));
            } else if (visible_computer_field_[i][j] == symbols::injured_ship) {
                init_pair(32, COLOR_RED, COLOR_BLACK);
                wattron(window_computer_field, COLOR_PAIR(32));
                mvwprintw(window_computer_field, 2 * i + 2, 4 * j + 2, "%c", visible_computer_field_[i][j]);
                wattroff(window_computer_field, COLOR_PAIR(32));
            } else if (visible_computer_field_[i][j] == symbols::miss) {
                init_pair(34, COLOR_YELLOW, COLOR_BLACK);
                wattron(window_computer_field, COLOR_PAIR(34));
                mvwprintw(window_computer_field, 2 * i + 2, 4 * j + 2, "%c", visible_computer_field_[i][j]);
                wattroff(window_computer_field, COLOR_PAIR(34));
            }
            use_default_colors();
        }
    }
    wrefresh(window_computer_field);
}


void WINDOW_GAME_COMPUTER_FIELD::move_up() {
    if (cur_x != 0) --cur_x;
}


void WINDOW_GAME_COMPUTER_FIELD::move_down() {
    if (cur_x != 9) ++cur_x;
}


void WINDOW_GAME_COMPUTER_FIELD::move_left() {
    if (cur_y != 0) --cur_y;
}


void WINDOW_GAME_COMPUTER_FIELD::move_right() {
    if (cur_y != 9)++cur_y;
}


bool WINDOW_GAME_COMPUTER_FIELD::ability_move(int x, int y) {
    return visible_computer_field_[x][y] == symbols::sea;
}


bool WINDOW_GAME_COMPUTER_FIELD::user_move(int x, int y) {
    if (computer_field_[x][y] == symbols::ship) {
        visible_computer_field_[x][y] = symbols::injured_ship;
        computer_field_[x][y] = symbols::injured_ship;
        computer_field_[x][y] = symbols::injured_ship;
        return true;
    }
    visible_computer_field_[x][y] = symbols::miss;
    computer_field_[x][y] = symbols::miss;
    return false;
}


bool WINDOW_GAME_COMPUTER_FIELD::is_ship_sunk(int x, int y, std::string direction) {
    try {
        if (computer_field_.at(x + 1)[y] == symbols::ship) {
            return false;
        }
    }
    catch (std::out_of_range &e) {}
    try {
        if (computer_field_.at(x - 1)[y] == symbols::ship) {
            return false;
        }
    }
    catch (std::out_of_range &e) {}
    try {
        if (computer_field_[x].at(y + 1) == symbols::ship) {
            return false;
        }
    }
    catch (std::out_of_range &e) {}
    try {
        if (computer_field_[x].at(y - 1) == symbols::ship) {
            return false;
        }
    }
    catch (std::out_of_range &e) {}


    if (direction == "") {
        try {
            if (visible_computer_field_.at(x + 1)[y] == symbols::injured_ship) {
                if (!is_ship_sunk(x + 1, y, "right")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
        try {
            if (visible_computer_field_.at(x - 1)[y] == symbols::injured_ship) {
                if (!is_ship_sunk(x - 1, y, "left")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
        try {
            if (visible_computer_field_[x].at(y + 1) == symbols::injured_ship) {
                if (!is_ship_sunk(x, y + 1, "down")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
        try {
            if (visible_computer_field_[x].at(y - 1) == symbols::injured_ship) {
                if (!is_ship_sunk(x, y - 1, "up")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
    } else if (direction == "right") {
        try {
            if (visible_computer_field_.at(x + 1)[y] == symbols::injured_ship) {
                if (!is_ship_sunk(x + 1, y, "right")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
    } else if (direction == "left") {
        try {
            if (visible_computer_field_.at(x - 1)[y] == symbols::injured_ship) {
                if (!is_ship_sunk(x - 1, y, "left")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
    } else if (direction == "down") {
        try {
            if (visible_computer_field_[x].at(y + 1) == symbols::injured_ship) {
                if (!is_ship_sunk(x, y + 1, "down")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
    } else if (direction == "up") {
        try {
            if (visible_computer_field_[x].at(y - 1) == symbols::injured_ship) {
                if (!is_ship_sunk(x, y - 1, "up")) {
                    return false;
                }
            }
        }
        catch (std::out_of_range &e) {}
    }
    return true;
}


void WINDOW_GAME_COMPUTER_FIELD::automatic_bombardment() {
    int x = cur_x;
    int y = cur_y;
    bool direction = false;
    while (true) {
        --y;
        try {
            if (computer_field_.at(x).at(y) == symbols::sea || computer_field_.at(x).at(y) == symbols::miss) {
                break;
            }
        } catch (std::out_of_range &e) {
            break;
        }
    }
    ++y;

    while (true) {
        --x;
        try {
            if (computer_field_.at(x).at(y) == symbols::sea || computer_field_.at(x).at(y) == symbols::miss) {
                break;
            }
        } catch (std::out_of_range &e) {
            break;
        }
    }
    ++x;

    try {
        if (computer_field_.at(x + 1).at(y) == symbols::injured_ship) {
            direction = true;
        }
    } catch (std::out_of_range &e) {}

    if (direction) {
        for (int i = -1; i < 2; ++i) {
            try {
                visible_computer_field_.at(x - 1).at(y + i) = symbols::miss;
                computer_field_.at(x - 1).at(y + i) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
        while (true) {
            try {
                if (computer_field_.at(x).at(y) == symbols::sea ||
                    computer_field_.at(x).at(y) == symbols::miss) {
                    break;
                }
            } catch (std::out_of_range &e) {
                break;
            }
            visible_computer_field_[x][y] = symbols::injured_ship;
            computer_field_[x][y] = symbols::injured_ship;
            try {
                visible_computer_field_.at(x).at(y + 1) = symbols::miss;
                computer_field_.at(x).at(y + 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
            try {
                visible_computer_field_.at(x).at(y - 1) = symbols::miss;
                computer_field_.at(x).at(y - 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
            ++x;
        }
        for (int i = -1; i < 2; ++i) {
            try {
                visible_computer_field_.at(x).at(y + i) = symbols::miss;
                computer_field_.at(x).at(y + i) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
    } else {
        for (int i = -1; i < 2; ++i) {
            try {
                visible_computer_field_.at(x + i).at(y - 1) = symbols::miss;
                computer_field_.at(x + i).at(y - 1) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
        while (true) {
            try {
                if (computer_field_.at(x).at(y) == symbols::sea ||
                    computer_field_.at(x).at(y) == symbols::miss) {
                    break;
                }
            } catch (std::out_of_range &e) {
                break;
            }
            visible_computer_field_[x][y] = symbols::injured_ship;
            computer_field_[x][y] = symbols::injured_ship;
            try {
                visible_computer_field_.at(x + 1).at(y) = symbols::miss;
                computer_field_.at(x + 1).at(y) = symbols::miss;
            } catch (std::out_of_range &e) {}
            try {
                visible_computer_field_.at(x - 1).at(y) = symbols::miss;
                computer_field_.at(x - 1).at(y) = symbols::miss;
            } catch (std::out_of_range &e) {}
            ++y;
        }
        for (int i = -1; i < 2; ++i) {
            try {
                visible_computer_field_.at(x + i).at(y) = symbols::miss;
                computer_field_.at(x + i).at(y) = symbols::miss;
            } catch (std::out_of_range &e) {}
        }
    }
}


bool WINDOW_GAME_COMPUTER_FIELD::availability_of_ships() const {
    for (size_t i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (computer_field_[i][j] == symbols::ship) {
                return true;
            }
        }
    }
    return false;
}


void WINDOW_GAME_COMPUTER_FIELD::interface() {
    while (true) {
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
                if (ability_move(cur_x, cur_y)) {
                    if (user_move(cur_x, cur_y)) {
                        if (is_ship_sunk(cur_x, cur_y)) {
                            automatic_bombardment();
                            break;
                        }
                    } else {
                        display();
                        return;
                    }
                }
                break;
        }
        display();
    }
}
