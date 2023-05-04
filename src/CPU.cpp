#include "cpu.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

CPU::CPU(){}

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
    std::cout<< "P1 is "<< py->_side<<"\n";
    std::cout<< "P1 is "<< _side<<"\n";
}
// void CPU::updatePlayer(sf::Event &event) {
    
// }

// float CPU::getPDisp(char axis = 'y')
// {
//     // axis = 'x' | 'y'
//     sf::Vector2f Pdisp = track_p->getPosition();
//     sf::Vector2f Cdisp = self->getPosition();
//     float p_handler{};
//     float cpu_handler{};
//     float final_disp{};
//     if (axis == 'x')
//     {
//         p_handler = Pdisp.x;
//         cpu_handler = Cdisp.x;   
//     }
//     else if (axis == 'y')
//     {
//         p_handler = Pdisp.y;
//         cpu_handler = Cdisp.y;
//     }
//     final_disp = p_handler - cpu_handler;
//     std::cout<<"Axis: "<<axis<<"\n pos is "<<final_disp;
//     return final_disp;
// }

// // void get_b_disp(char axis, Ball ball);
void CPU::updateCpu()
{
    float P_disp_y = getPDisp('y');
    
    if (P_disp_y> 0.0)
    {
        self->vel = track_p->vel;
    }
    else if (P_disp_y > 0.0)
    {
        self->vel = track_p->vel;
    }
    else if (P_disp_y == 0.0)
    {
        self->vel = 0;
    }
// // }
// void CPU::moveCpu()
// {
//     self->move(0, self->vel);
// }