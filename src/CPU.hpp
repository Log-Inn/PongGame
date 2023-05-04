#ifndef CPU_HPP
#define CPU_HPP

#include "ball.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>

class CPU : public Player
{
private:
    float getPDisp(char axis = 'y');
    float get_b_disp(char axis, Ball ball);
public:
    CPU();
    // checks relative disp of entity from CPU, get_r_disp(Ball, Player)
    Player* track_p;

    // store self displacement
    // float self_dispx{0};
    // float self_dispy{0};
    
    // stores Ball displacement
    // float B_dispx{0};
    // float B_dispy{0};

    // stores Player y-displacement
    // float P_dispy{0};
    
    void createCpu(Player* py);
    void moveCpu();
    //float getPDisp(char axis);
    // void updatePlayer(sf::Event &event) override;
    // void movePlayer() override;
};

#endif // CPU_HPP


