#include "Connect4.h"
#include <math.h>

Connect4::Connect4(int h, int w)
{
    this->h = h;
    this->w = w;
    board.resize(h, std::vector<int>(w, EMPTY));
    turn = PLAYER1;
    turns_played = 0;
    status = STATUS_ONGOING;
}

int Connect4::step(int col)
{
    if (status != STATUS_ONGOING)
        return status;

    if (!(col >= 1 && col <= w))
        return status = STATUS_ILLEGAL_MOVE;

    int next_row = num_symbols_in_column(--col);
    if (next_row >= h)
        return status = STATUS_ILLEGAL_MOVE;

    board[next_row][col] = turn;
    turns_played++;

    int winner = check_winner(next_row, col);
    if (winner == PLAYER1)
        return status = STATUS_PLAYER1_WON;
    else if (winner == PLAYER2)
        return status = STATUS_PLAYER2_WON;

    if (turns_played == h * w)
        return status = STATUS_DRAW;

    turn = player_not_on_turn();
    return status;
}

int Connect4::step(sf::RenderWindow& win, int col)
{
    if (status != STATUS_ONGOING)
        return status;

    if (!(col >= 1 && col <= w))
        return status = STATUS_ILLEGAL_MOVE;

    int next_row = num_symbols_in_column(--col);
    if (next_row >= h)
        return status = STATUS_ILLEGAL_MOVE;

    for (int row = h - 1; row > next_row; row--) {
        board[row][col] = turn;
        this->draw_board(win);
        win.display();
        sf::sleep(sf::milliseconds(200 / h * sqrt(row)));
        board[row][col] = EMPTY;
    }
    board[next_row][col] = turn;
    turns_played++;

    int winner = check_winner(next_row, col);
    if (winner == PLAYER1)
        return status = STATUS_PLAYER1_WON;
    else if (winner == PLAYER2)
        return status = STATUS_PLAYER2_WON;

    if (turns_played == h * w)
        return status = STATUS_DRAW;

    turn = player_not_on_turn();
    return status;
}

int Connect4::num_symbols_in_column(int col) const
{
    int row = 0;
    while (row < h && board[row][col] != EMPTY)
        row++;
    return row;
}

int Connect4::check_winner(int row, int col) const
{
    int who = board[row][col];
    std::vector<int> dir_row = { 0, 1, 1, -1 }, dir_col = { 1, 0, 1, 1 };

    for (int i = 0; i < 4; i++) {
        int delta_r = dir_row[i], delta_c = dir_col[i], count = 0, r = row + delta_r, c = col + delta_c;
        while (r >= 0 && r < h && c >= 0 && c < w && board[r][c] == who) {
            count++;
            r += delta_r;
            c += delta_c;
        }
        delta_r = -delta_r;
        delta_c = -delta_c;
        r = row + delta_r;
        c = col + delta_c;
        while (r >= 0 && r < h && c >= 0 && c < w && board[r][c] == who) {
            count++;
            r += delta_r;
            c += delta_c;
        }
        if (count + 1 >= 4)
            return who;
    }
    return EMPTY;
}

int Connect4::get_status() const { return status; }

std::string Connect4::get_status_desc() const
{
    switch (status) {
    case STATUS_DRAW:
        return "The game is a draw";
    case STATUS_PLAYER1_WON:
        return "The yellow player won";
    case STATUS_PLAYER2_WON:
        return "The red player won";
    case STATUS_ILLEGAL_MOVE:
        return "An illegal move was played.\n Game aborted";
    default:
        return "";
    }
}

std::vector<std::vector<int>> Connect4::get_board() const { return board; }

void Connect4::set_board(std::vector<std::vector<int>> board) { this->board = board; }

int Connect4::player_not_on_turn() const { return PLAYER1 + PLAYER2 - turn; }

int Connect4::player_on_turn() const { return turn; }

void Connect4::draw_board(sf::RenderWindow& win) const
{
    win.clear(sf::Color::Blue);
    for (int r = h - 1; r >= 0; r--) {
        for (int c = 0; c < w; c++) {
            unsigned int size = std::min(win.getSize().x / w, win.getSize().y / h);
            unsigned int pos_x = win.getSize().x * c / w, pos_y = win.getSize().y * (h - 1 - r) / h;
            sf::CircleShape p(size / 2), out(size / 3), mid(size / 5), in(size / 15);
            p.setOutlineColor(sf::Color(0, 0, 139));
            p.setOutlineThickness(-0.05f * size);
            out.setFillColor(sf::Color::Transparent);
            mid.setFillColor(sf::Color::Transparent);
            in.setFillColor(sf::Color::Transparent);
            if (board[r][c] == PLAYER1) {
                p.setFillColor(sf::Color::Yellow);
                out.setOutlineColor(sf::Color(247, 127, 0));
                out.setOutlineThickness(3);
                mid.setOutlineColor(sf::Color(247, 127, 0));
                mid.setOutlineThickness(3);
                in.setOutlineColor(sf::Color(247, 127, 0));
                in.setOutlineThickness(3);
            } else if (board[r][c] == PLAYER2) {
                p.setFillColor(sf::Color::Red);
                out.setOutlineColor(sf::Color(139, 0, 23));
                out.setOutlineThickness(3);
                mid.setOutlineColor(sf::Color(139, 0, 23));
                mid.setOutlineThickness(3);
                in.setOutlineColor(sf::Color(139, 0, 23));
                in.setOutlineThickness(3);
            } else
                p.setFillColor(sf::Color::White);
            p.setPosition(sf::Vector2f(pos_x, pos_y));
            out.setPosition(sf::Vector2f(pos_x + size / 2 - size / 3, pos_y + size / 2 - size / 3));
            mid.setPosition(sf::Vector2f(pos_x + size / 2 - size / 5, pos_y + size / 2 - size / 5));
            in.setPosition(sf::Vector2f(pos_x + size / 2 - size / 15, pos_y + size / 2 - size / 15));
            win.draw(p);
            win.draw(out);
            win.draw(mid);
            win.draw(in);
        }
    }
}