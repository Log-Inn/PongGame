#include "player.hpp"
#include "pong.hpp"
#include <iostream>

int main()
{
    std::cout << "Enter desired framerate:\n";
    int framerate = 0;
    std::cin >> framerate;
    Pong pong(framerate);
    pong.run();
    return 0;
}