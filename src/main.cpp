#include "player.hpp"
#include "pong.hpp"
#include <iostream>

int main()
{
    std::cout << "Pong\n";
    Pong pong;
    pong.run();
    return 0;
}