#ifndef __CONNECT4_H
#define __CONNECT4_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

#define STATUS_ONGOING 0
#define STATUS_PLAYER1_WON 1
#define STATUS_PLAYER2_WON 2
#define STATUS_DRAW 3
#define STATUS_ILLEGAL_MOVE 4

class Connect4 {
    std::vector<std::vector<int>> board;

public:
    int h, w, status, turn, turns_played;
    Connect4(int h = 6, int w = 7);
    int step(int);
    int step(sf::RenderWindow&, int);
    int num_symbols_in_column(int) const;
    int check_winner(int, int) const;
    int get_status() const;
    std::string get_status_desc() const;
    std::vector<std::vector<int>> get_board() const;
    void set_board(std::vector<std::vector<int>>);
    int player_on_turn() const;
    int player_not_on_turn() const;
    void draw_board(sf::RenderWindow&) const;
};

#endif