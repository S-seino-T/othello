#pragma once
#include "util.hpp"
enum class desc
{
    black,
    white,
    space,
    wall
};

class board
{
    std::vector<desc> b;

    desc& at(int, int);
    bool is_turnover_onedir(int, int, int, int, desc) const;
    void flip_onedir(int,int,int,int,desc);
public:
    board();
    virtual ~board();

    desc get_desc(int, int) const;
    desc opponent(desc) const;
    desc player(desc) const;
    void print() const;
    void print_placeable(desc) const;
    bool is_turnover(int, int, desc) const;
    bool is_placeable(desc) const;
    bool is_playable() const;
    void flip(int,int,desc);
};