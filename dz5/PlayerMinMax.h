#ifndef __PLAYER_MIN_MAX_H
#define __PLAYER_MIN_MAX_H

#include "Connect4.h"
#include <vector>

#define WIN_SCORE 8
#define EXPLORATION_FACTOR 1.414213562

double uctValue(int, int, int);

class State {
public:
    Connect4 env;
    int winScore, visitCount, player, lastMove;
    State();
    void setBoard(const std::vector<std::vector<int>>&);
    int getOpponent() const;
    void incrementVisit();
    std::vector<State*> getAllPossibleStates();
};

class Node {
    Node* parent;
    std::vector<Node*> children;

public:
    State* state;
    Node(State*);
    void addChild(Node*);
    Node* getParent();
    std::vector<Node*> getChildren();
    Node* getRandomChild();
    Node* findBestChild();
    void expand();
    ~Node();
};

class PlayerMinMax {
    int whoami, max_depth;

public:
    PlayerMinMax(int, int);
    int get_action(const std::vector<std::vector<int>>&&, int);
    int rollout(Node*);
};

Node* selectPromisingNode(Node*);
void backProp(Node*, int);

#endif