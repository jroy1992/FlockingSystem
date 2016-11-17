#ifndef FLOCK_H_
#define FLOCK_H_

#include"Boid.h"
#include "Image.h"
#include<vector>
#include<memory>

class Flock
{
protected:
    std::vector<Boid> m_boids;

public:

    Flock(Boid _b, int _num);

    //calls run func of Boid class for each boid
    void runflock();

    //adds num amount of new Boid to the flock
    void addBoid(Boid _b, int _num);

    void draw(Image &_i)const;
};

#endif
