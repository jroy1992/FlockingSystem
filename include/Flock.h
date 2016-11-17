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

    Flock(Boid b, int num);

    void runflock(); //calls run func of Boid class for each boid

    void addBoid(Boid b, int num); //adds num amount of new Boid to the flock

    void draw(Image &_i)const;
};

#endif
