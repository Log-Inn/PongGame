#ifndef CPU_HPP
#define CPU_HPP

#include <iostream>
#include "player.hpp"
#include <tuple>

class CPU : public Player
{
private:
    // keep everything as a public var for convenience
public:
    CPU();
    // checks relative disp of entity from CPU, get_r_disp(Ball, Player)
    // stores Ball displacement
    double B_dispx{0};
    double B_dispy{0};

    // stores Player displacement
    double P_dispx{0};
    double P_dispy{0};
    
    void create_ai(Player py);
    void get_p_disp(char axis, Player py);
    // void get_b_disp(char axis, Ball ball);
    void updateCPU();
    void move_ai();
    


    // creates the rectangle/player. side is either 'L' or 'R'
    // void create() { if (side == 'L') }
};

#endif // CPU_HPP

// ! FFFFFUUUUUUCCCCCK WHY WONT YOU 
// ! WORK DUMB MACHINE STOP BEING RETARDED 
// !CPU MEANS CPU YOU COCK
