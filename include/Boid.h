#ifndef BOID_H_
#define BOID_H_
#include"PVector.h"
#include "Image.h"
#include<vector>

class Boid
{
public:

    PVector m_position;
    PVector m_velocity;
    PVector m_acceleration;

    float m_r;
    float m_maxspeed;
    float m_maxforce;

    Boid():m_acceleration(0.0f,0.0f),m_velocity(1.0f,1.0f){}

    Boid(PVector _pos):m_position(_pos.getX(),_pos.getY())
    {
        m_r = 3.0;
        m_maxspeed = 4;
        m_maxforce = 0.1;
    }

    void run(std::vector<Boid>);

    void applyForce(PVector);

    void flock(std::vector<Boid>);

    void update();

    void draw(Image &i) const;

    PVector seek(PVector);

    PVector separate(std::vector<Boid>);

    PVector align(std::vector<Boid>);

    PVector cohesion(std::vector<Boid>);

    PVector swarm(std::vector<Boid>);

    void view(std::vector<Boid>);

};

#endif
