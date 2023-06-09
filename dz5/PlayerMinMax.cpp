#include "PlayerMinMax.h"
#include "Connect4.h"
#include <math.h>
#include <random>
#include <vector>

// ovo dvoje je potrebno da radi i na windowsima i na linuxu
#ifndef __INT_MAX__
#define __INT_MAX__ INT_MAX
#endif

#ifndef __DBL_MAX__
#define __DBL_MAX__ DBL_MAX
#endif

Node::Node(State* state)
{
    this->state = state;
    this->parent = nullptr;
    this->children = std::vector<Node*>();
}

void Node::addChild(Node* child) { children.push_back(child); }

Node* Node::getParent() { return this->parent; }

std::vector<Node*> Node::getChildren() { return this->children; }

Node* Node::getRandomChild()
{
    if (children.empty())
        return nullptr;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, children.size() - 1);
    return children[dis(gen)];
}

Node* Node::findBestChild()
{
    int parentVisit = this->state->visitCount;
    std::vector<Node*> children = this->children;
    Node* maxi = children[0];

    for (Node* child : children) {
        double uctValue1 = uctValue(parentVisit, child->state->winScore, child->state->visitCount);
        double uctValue2 = uctValue(parentVisit, maxi->state->winScore, maxi->state->visitCount);
        if (uctValue1 >= uctValue2)
            maxi = child;
    }

    return maxi;
}

void Node::expand()
{
    std::vector<State*> possibleStates = this->state->getAllPossibleStates();
    for (State* state : possibleStates) {
        Node* newNode = new Node(state);
        newNode->parent = this;
        newNode->state->player = this->state->getOpponent();
        this->addChild(newNode);
    }
}

Node::~Node()
{
    for (Node* child : children) {
        delete child->state;
        delete child;
    }
    parent = nullptr;
}

State::State()
{
    winScore = 0;
    visitCount = 0;
    player = PLAYER1;
    lastMove = -1;
    env = Connect4();
}

void State::setBoard(const std::vector<std::vector<int>>& board) { env.set_board(board); }

int State::getOpponent() const { return (player == PLAYER1) ? PLAYER2 : PLAYER1; }

void State::incrementVisit() { visitCount++; }

std::vector<State*> State::getAllPossibleStates()
{
    std::vector<State*> allPossibleStates;

    for (int i = 0; i < env.w; i++) {
        if (env.num_symbols_in_column(i) < env.h) {
            State* tempState = new State();
            tempState->setBoard(env.get_board());
            tempState->env.status = env.status;
            tempState->env.turn = player;

            tempState->env.step(i + 1);
            tempState->lastMove = i;

            allPossibleStates.push_back(tempState);
        }
    }
    return allPossibleStates;
}

double uctValue(int totalVisit, int nodeWinScore, int nodeVisit)
{
    if (nodeVisit == 0)
        return __DBL_MAX__;
    double left = (double)nodeWinScore / nodeVisit, right = sqrt(log(totalVisit + 1) / nodeVisit);
    return left + EXPLORATION_FACTOR * right;
}

PlayerMinMax::PlayerMinMax(int whoami, int max_steps)
{
    this->whoami = whoami;
    this->max_depth = max_steps;
}

int PlayerMinMax::get_action(const std::vector<std::vector<int>>&& board, int status)
{
    State* temp_state = new State();
    Node* rootNode = new Node(temp_state);
    rootNode->state->setBoard(board);
    rootNode->state->player = whoami;

    int num_steps = 0;
    while (num_steps++ <= max_depth) {
        Node* promisingNode = selectPromisingNode(rootNode);

        if (promisingNode->state->env.status == STATUS_ONGOING)
            promisingNode->expand();

        Node* nodeToExplore = promisingNode;
        if (!promisingNode->getChildren().empty())
            nodeToExplore = promisingNode->getRandomChild();

        int playoutResult = rollout(nodeToExplore);
        backProp(nodeToExplore, playoutResult);
    }

    const std::vector<Node*>& children = rootNode->getChildren();
    int b = 0;
    for (size_t i = 0; i < children.size(); i++) {
        double score2 = (double)(children[b]->state->winScore) / (children[b]->state->visitCount + 1);
        double score1 = (double)(children[i]->state->winScore) / (children[i]->state->visitCount + 1);
        if (score1 >= score2)
            b = i;
    }

    int bestMove = children[b]->state->lastMove + 1;
    delete temp_state;
    delete rootNode;
    return bestMove;
}

int PlayerMinMax::rollout(Node* node)
{
    State* tempState = new State(*node->state);
    int boardStatus = tempState->env.status;
    bool firstWon = boardStatus == STATUS_PLAYER1_WON && tempState->player == PLAYER2;

    if (firstWon || (boardStatus == STATUS_PLAYER2_WON && tempState->player == PLAYER1)) {
        node->getParent()->state->winScore = -__INT_MAX__;
        delete tempState;
        return boardStatus;
    }

    while (boardStatus == STATUS_ONGOING) {
        tempState->env.step(rand() % tempState->env.w + 1);
        boardStatus = tempState->env.status;
    }

    int result = boardStatus;
    delete tempState;
    return result;
}

Node* selectPromisingNode(Node* rootNode)
{
    Node* node = rootNode;
    while (!node->getChildren().empty()) {
        node = node->findBestChild();
    }
    return node;
}

void backProp(Node* nodeToExplore, int result)
{
    int winner = (result == STATUS_PLAYER1_WON) ? PLAYER1 : PLAYER2;
    bool draw = (result == STATUS_DRAW || result == STATUS_ILLEGAL_MOVE);
    Node* temp = nodeToExplore;

    while (temp != nullptr) {
        temp->state->incrementVisit();
        if (temp->state->player == winner && !draw)
            temp->state->winScore -= WIN_SCORE;
        else if (!draw)
            temp->state->winScore += WIN_SCORE;
        temp = temp->getParent();
    }
}