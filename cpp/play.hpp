#pragma once
#include "util.hpp"
#include "board.hpp"

class co
{
public:
    int row;
    int column;

    co();
    virtual ~co();
};

class play
{
    const desc m_desc;
public:
    play(desc);
    virtual ~play();
    desc getter() const;

    virtual co put_desc(shared_ptr<board>){co r; return r;};
};

class player : public play
{
public:
    player(desc d);
    co put_desc(shared_ptr<board>) override;
};

class random_enemy : public play
{
public:
    random_enemy(desc d);
    co put_desc(shared_ptr<board>) override;
};

