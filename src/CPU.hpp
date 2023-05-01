#ifndef CPU_HPP
#define CPU_HPP

class CPU : public Player::Player
{
private:
public:

    // checks relative disp of entity from CPU, get_r_disp(Ball, Player)
    int B_dispx = 500;
    int B_dispy = 300;

    int P_dispx = 1000;
    int P_dispy = 1000;
    
    void get_r_disp();
    
    void move_cpu();
    void create_AI(Player p1);

    // creates the rectangle/player. side is either 'L' or 'R'
    // void create() { if (side == 'L') }
};


#endif // CPU_HPP
