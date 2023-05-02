#ifndef CPU_HPP
#define CPU_HPP

#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <tuple>

class CPU : public Player
{
private:
    // keep everything as a public var for convenience
public:
    CPU();
    // checks relative disp of entity from CPU, get_r_disp(Ball, Player)
    
    Player track_p;
    Player self;
    // store self displacement
    float self_dispx{0};
    float self_dispy{0};
    
    // stores Ball displacement
    float B_dispx{0};
    float B_dispy{0};

    // stores Player y-displacement
    float P_dispy{0};
    
    void createAi(Player py);
    float getPDisp(char axis, Player py);
    // void get_b_disp(char axis, Ball ball);
    void updateCpu(Player py);
    void moveCpu();

    // creates the rectangle/player. side is either 'L' or 'R'
    // void create() { if (side == 'L') }
};

#endif // CPU_HPP

// ! FFFFFUUUUUUCCCCCK WHY WONT YOU 
// ! WORK DUMB MACHINE STOP BEING RETARDED 
// !CPU MEANS CPU YOU COCK
