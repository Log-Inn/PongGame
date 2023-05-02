#include "cpu.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>

CPU::CPU()
{
    Player();
}

void CPU::create_ai(Player player)
{
    Player cpu;
    if (player.side == 'L')
    {
        cpu.create('R');
    }
    else if (player.side == 'R')
    {
        cpu.create('L');
    }
}

void get_p_disp(char axis, Player player)
{


}
// void get_b_disp(char axis, Ball ball);
void updateCPU();
void move_ai();