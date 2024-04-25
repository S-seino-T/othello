#pragma once
#include "util.hpp"
#include "play.hpp"
#include "heap.hpp"

class eval_play : public play
{
    const vector<vector<int>> eval_sheet;

public:

    eval_play(desc d);
    inline int at(int, int);
    co put_desc(shared_ptr<board>) override;
    virtual co put_desc_eval(shared_ptr<board>){co r; return r;};
};

class once_ahead_enemy : public eval_play
{
    vector<vector<int>> score;

    int eval_count(board);
public:

    once_ahead_enemy(desc d);
    void eval(shared_ptr<board>);
    co put_desc_eval(shared_ptr<board>) override;
};

class negamax_enemy : public eval_play
{
    const int dp=6;
    int eval(board,desc,int,int,int);
    int eval_count(board,desc);
public:
    negamax_enemy(desc d);
    ~negamax_enemy();
    co put_desc_eval(shared_ptr<board>) override;
};