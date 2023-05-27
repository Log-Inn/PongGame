#ifndef CPU_HPP
#define CPU_HPP

#include "ball.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>

class CPU : public Player
{
private:

public:
    CPU();
    // checks relative disp of entity from CPU, get_r_disp(Ball, Player)
    Player* track_p;
    Ball* eball;

    void hookball(Ball* b);
    void createCpu(Player* py);
    void moveCpu();

    // TODO change this to template func
    //float getPDisp(char axis);
    float getPDisp(char axis = 'y');
    float getBDisp(char axis = 'y');

    // void updatePlayer(sf::Event &event) override;
    // void movePlayer() override;
};

#endif // CPU_HPP


