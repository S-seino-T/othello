#include "util.hpp"
#include "game.hpp"

int main()
{
    unique_ptr<game> g(new game);
    g->Game(); 
}