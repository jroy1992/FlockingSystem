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

void Flock::runflock()
{
    int count=0;
    for(Boid &_b : m_boids)
    {
        _b.run(m_boids);
    }
}

void Flock::addBoid(Boid _b, int _num)
{
    for(size_t i=0; i<_num; i++)
        m_boids.push_back(_b);
    runflock();
}

void Flock::draw(Image &_i)const
{
    for(auto &p : m_boids)
        p.draw(_i);
}
