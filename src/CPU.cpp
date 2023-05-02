#include "cpu.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

CPU::CPU()
{
    Player cpu2;
    this->self = cpu2;
    this->self_dispx = 0.0;
    this->self_dispy = 0.0;
}

void CPU::createAi(Player py)
{
    this->track_p = py;
    if (py.side == 'L')
    {
        self.create('R');
    }
    else if (py.side == 'R')
    {
        self.create('L');
    }
    std::cout<<"P1 is "<<track_p.side<<"\n";
    std::cout<<"CPU is "<<self.side;
}

float get_relative_p_disp(char axis = 'y')
{
    // axis = 'x' | 'y'
    sf::Vector2f Pdisp = track_p.getPosition();
    sf::Vector2f Cdisp = self.getPosition();
    float p_handler{};
    float cpu_handler{};
    float final_disp{};
    if (axis == 'x')
    {
        p_handler = Pdisp.x;
        cpu_handler = Cdisp.x;
        final_disp = p_handler - cpu_handler;
    }
    else if (axis == 'y')
        p_handler = Pdisp.y;
        cpu_handler = Cdisp.y;
        final_disp = p_handler - cpu_handler;
    }
    cpu_handler = 
    std::cout<<"Axis: "<<axis<<"\n pos is "<<handler;
    return final_disp;
}

// void get_b_disp(char axis, Ball ball);
void CPU::update_Cpu()
{
    if (get_relative_p_disp() >= 0)
    {
        self.vel = -track_p.vel;
    }
    else if (get_relative_p_disp() <= 0)
    {
        self.vel = track_p.vel;
    }
    
}
void moveAi()
{
    self.move(0,self.vel)
}