#include "cpu.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

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
void CPU::hookball(Ball* beep)
{
    eball = beep;
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

float CPU::getBDisp(char axis)
{
    // axis = 'x' | 'y'
    sf::Vector2f Bdisp = eball->getPosition();
    sf::Vector2f Cdisp = getPosition();
    float b_handler{};
    float cpu_handler{};
    float final_disp{};
    if (axis == 'x')
    {
        // note to self: you don't need to use the center since we only check the diff
        b_handler = Bdisp.x;
        cpu_handler = Cdisp.x;
    }
    else if (axis == 'y')
    {
        b_handler = Bdisp.y;
        cpu_handler = Cdisp.y;
    }
    final_disp = cpu_handler - b_handler;
    return final_disp;
}

// void get_b_disp(char axis, Ball ball);
void CPU::moveCpu()
{
    float P_disp_y = getPDisp('y');
    float B_disp_x = getBDisp('x');
    float B_disp_y = getBDisp('y');
    // threshold before cpu follows ball
    float thresh = hook->getWindowWidth() * 0.5;
    if (B_disp_x>thresh)
    {
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
        /* *
        add functionality to move 
        until x has been reached
        */
        // int n = rand() % 100;
        // if (n < 30)
        // {
        //     vel = -5;
        // }
        // else if (n > 70)
        // {
        //     vel = 5;
        // }
        // else 
        // {
        //     vel = 0;
        // }
    }
    if (B_disp_x<thresh)
    {
        if (B_disp_y> 10)
        {
            // if you wanna put him on steroids
            vel -= 0.2;
            //vel = -5;
        }
        else if (B_disp_y < 10.0)
        {
            // if you wanna put him on steroids
            vel += 0.2;
            //vel = 5;
        }
        else if (B_disp_y == 0.0)
        {
            vel = 0;
        }
    }
    movePlayer();
}

// void CPU::movePlayer()
// {
//     this->move(0, 5);
// }
