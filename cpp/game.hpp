#pragma once
#include "util.hpp"
#include "board.hpp"
#include "play.hpp"
#include "AI.hpp"

class game
{
    shared_ptr<board> now_board;
    vector<tuple<board,desc>> log;
    desc p;
    shared_ptr<play> p1;
    shared_ptr<play> p2;

    bool OneLoop();
public:
    game();
    virtual ~game();
    bool Initialize();
    void Loop();
    void Terminate();
    void Game();
};