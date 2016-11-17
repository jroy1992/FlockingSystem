#include "Boid.h"
#include "PVector.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include<list>

//***      Code modified from the work of Daniel Shiffman on github: The-Nature-of-Code-Examples   ***

void Boid::run(std::vector<Boid> boids)
{
    flock(boids);
    update();
}

void Boid::update()
{
   //updating the varying attributes of the boid
    m_velocity+=m_acceleration;
    m_velocity.limit(m_maxspeed);
    m_position+=m_velocity;

    // resetting acceleration to 0 after each cycle
    m_acceleration.mult(0);
}

void Boid::applyForce(PVector _force)
{
    /* applying force to make the boid move.
     * F = ma Can have "m" in case the boids are of diff sizes.
     */
    m_acceleration+=_force;
}


void Boid::flock(std::vector<Boid> boids)
{
    PVector sep = separate(boids);
    PVector ali = align(boids);
    PVector coh = cohesion(boids);
    PVector swm = swarm(boids);

    /* assigning weights to individual behaviors
     * and applying the returned steering force
     */

    sep.mult(2);
    ali.mult(1.0);
    coh.mult(1.0);
    swm.mult(3);

    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
    applyForce(swm);
}

void Boid::draw(Image &_i) const
{
    _i.setPixel(m_position.getX(), m_position.getY(), 255,0,0);
}


PVector Boid::seek(PVector _target)
{
    PVector desired = _target - m_position;
    desired.normalise();
    desired.limit(m_maxspeed);

    PVector steer = desired - m_velocity;
    steer.limit(m_maxforce);
    return steer;
}


// method to move away if a neighboring boid is within the line of sight
PVector Boid::separate(std::vector<Boid> _boids)
{
    float desiredseparation = 100.0f;
    PVector steer(0.0,0.0);
    int count = 0;

    for(Boid const &other : _boids)
    {
        float d = m_position.dist(m_position,other.m_position);
        if((d>0) && (d<desiredseparation))
        {
            //find the and add the distance between this boid's location and all neighbor boids' location
            PVector diff = m_position - other.m_position;
            diff.normalise();
            diff.div(d);
            steer+=diff;
            count++;
        }
    }

    if(count > 0)
    {
        //the average will be used as desired velocity for steering in opp direction to neighbors
        steer.div((float)count);
    }

    if(steer.mag() > 0)
    {
        steer.normalise();
        steer.mult(m_maxspeed);
        steer-=m_velocity;
        steer.limit(m_maxforce);
    }
    return steer;
}


// method to match a boid's velocity with that of its neighbors
PVector Boid::align(std::vector<Boid> _boids)
{
    float neighbourdist = 100;
    PVector sum(0,0);
    int count = 0;
    //desired velocity = avg velocity of all the boids
    for(Boid &other : _boids)
    {
        float d = m_position.dist(m_position, other.m_position);
        if((d>0) && (d<neighbourdist))
        {
            sum+=other.m_velocity;
            count++;
        }
    }
    if(count>0)
    {
        sum.div((float)count);
        sum.normalise();
        sum.mult(m_maxspeed);
        PVector steer = sum-m_velocity;
        steer.limit(m_maxforce);
        return steer;
    }
    else
        return PVector(0.0,0.0);
}

PVector Boid::cohesion(std::vector<Boid> _boids)     // boids ability to group together
{
    float neighbordist = 100;
    PVector sum(0,0);
    int count = 0;
    for(Boid &other : _boids)
    {
        float d = m_position.dist(m_position, other.m_position);
        if((d>0) && (d<neighbordist))
        {
            sum+=other.m_position;                 // add the positions of all the neigbors
            count++;
        }
    }
    if(count>0)
    {
        sum.div(count);                            // calculate the avg position
        return seek(sum);                          // seek the avg
    }
    else
        return PVector(0.0,0.0);
}

//********************************************** END *******************************************************


void Boid::view(std::vector<Boid> boids)
{
    float lineOfSight = 500;
    float viewAngle = M_PI/4;

    std::vector<Boid>::iterator it;

    PVector steer(0.0,0.0);
    int count = 500;
    PVector pos(x,y);

   // for(it=boids.begin(); it!=boids.end(); it++)
   // {
        theta = count*golden_angle;
        float r = sqrt(count)/sqrt(500);
        pos.setX(r*cos(theta));
        pos.setY(r*sin(theta));
        //m_position.setX(x);
        //m_position.setY(y);

        float dist = m_position.dist(m_position, pos);
        if(dist>0.1)
        {
            steer=seek(pos);
            steer-=m_velocity;
            //steer.limit(m_maxforce);
            applyForce(steer);

        }
        //count++;
  //  }
}

// method to gather the boids like swarms of insects
PVector Boid::swarm(std::vector<Boid> _boids)
{
    float lineOfSight = 500;
    float viewAngle = M_PI/4;
    std::vector<Boid>::iterator it;

    PVector steer(0.0,0.0);
    int count = 0;

    //the boid checks other boids within its viewAngle, finds the difference vector from each and directs it clockwise normally
    for(it=_boids.begin(); it!=_boids.end(); it++)
    {
        float dist = m_position.dist(m_position, it->m_position);
        PVector direction = m_position - it->m_position;
        float theta = m_velocity.angleBetween(m_velocity, direction);

        if((float)abs(theta)<viewAngle && dist>0 && dist<lineOfSight)
        {
            direction.getNormalClockwise();
            direction.normalise();
            direction.div(dist);
            steer+=direction;
            count++;
        }
    }

    if(count > 0)
    {
        steer.div((float)count);
    }

    if(steer.mag()>0)
    {
        steer.normalise();
        steer.mult(m_maxspeed);
        steer-=m_velocity;
        steer.limit(m_maxforce);
    }
    return steer;
}

