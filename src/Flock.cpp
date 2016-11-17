#include"Flock.h"
#include <random>

static std::mt19937 gen;

Flock::Flock(Boid _b, int _num)
{
    std::uniform_int_distribution<int> randPos(200,800);
    for(size_t i=0; i<_num; i++)
    {
        m_boids.push_back(_b);
        _b.m_position.setX(randPos(gen));
        _b.m_position.setY(randPos(gen));
    }
}

//***      Code modified from the work of Daniel Shiffman on github: The-Nature-of-Code-Examples   ***

void Flock::runflock()
{
    //passing the boid list to each boid
    for(Boid &b : m_boids)
    {
        b.run(m_boids);
    }
}

void Flock::addBoid(Boid _b, int _num)
{
    for(size_t i=0; i<_num; i++)
        m_boids.push_back(_b);
}
//******************************************* END *******************************************

void Flock::draw(Image &_i)const
{
    for(auto &p : m_boids)
        p.draw(_i);
}
