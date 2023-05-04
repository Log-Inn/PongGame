#include "cpu.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

CPU::CPU(){}

// * Mirror Player object 
void CPU::createCpu(Player* py)
{
    track_p = py;
    if ( py->_side == 'L')
    {
        create('R');
    }    
    if (py->_side == 'R')
    { 
        create('L');
    }
}

// void CPU::updatePlayer(sf::Event &event) {}

// * to get relative displacement for Player
// TODO Figure out if templates only work on basic datatypes, then can just do for both ball and player
// template <typename U>
// float max(CPU x, U y){}
float CPU::getPDisp(char axis)
{
    // axis = 'x' | 'y'
    sf::Vector2f Pdisp = track_p->getPosition();
    sf::Vector2f Cdisp = getPosition();
    float p_handler{};
    float cpu_handler{};
    float final_disp{};
    if (axis == 'x')
    {
        // note to self: you don't need to use the center since we only check the diff
        p_handler = Pdisp.x;
        cpu_handler = Cdisp.x;
    }
    else if (axis == 'y')
    {
        p_handler = Pdisp.y;
        cpu_handler = Cdisp.y;
    }
    final_disp = p_handler - cpu_handler;
    return final_disp;
}

// void get_b_disp(char axis, Ball ball);
void CPU::moveCpu()
{
    float P_disp_y = getPDisp('y');
    
    if (P_disp_y < 0.0)
    {
        vel = -5;
    }
    else if (P_disp_y > 0.0)
    {
        vel = 5;
    }
    else if (P_disp_y == 0.0)
    {
        vel = 0;
    }
    movePlayer();
}

// void CPU::movePlayer()
// {
//     this->move(0, 5);
// }
