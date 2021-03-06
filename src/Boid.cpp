#include "Boid.h"
#include "PVector.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include<list>

/// Modified from:
/// Daniel Shiffman (July, 2016). The-Nature-of-Code-Examples [online]
/// [Accessed 2016]. Available from: "https://github.com/shiffman/The-Nature-of-Code-Examples/tree/master/chp06_agents/NOC_6_09_Flocking".

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

    sep.mult(1);
    ali.mult(2.0);
    coh.mult(2.0);
    swm.mult(0);

    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
    applyForce(swm);
}

void Boid::draw(Image &_i) const
{
    _i.setPixel(m_position.getX(), m_position.getY(), 255,0,0);
}


//find the distance between boid location and target and steer towards target with maxForce
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
    float desiredseparation = 5.0f;
    PVector steer(0.0,0.0);
    int count = 0;

    for(Boid &other : _boids)
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


// boids ability to group together
PVector Boid::cohesion(std::vector<Boid> _boids)
{
    float neighbordist = 100;
    PVector sum(0,0);
    int count = 0;

    // add the positions of all the neigbors and seek the avg position
    for(Boid &other : _boids)
    {
        float d = m_position.dist(m_position, other.m_position);
        if((d>0) && (d<neighbordist))
        {
            sum+=other.m_position;
            count++;
        }
    }
    if(count>0)
    {
        sum.div(count);
        return seek(sum);
    }
    else
        return PVector(0.0,0.0);
}

/// End Citation


// method to gather the boids like swarms of flies
PVector Boid::swarm(std::vector<Boid> _boids)
{
    float lineOfSight = 500;
    float viewAngle = M_PI/4;
    std::vector<Boid>::iterator it;
    PVector center(512,360);
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
            /* the direction needs to be changed to getNormalClockwise() if they start moving out of the wi
             * working on the fix
             */
            direction.getNormalAntiClockwise();
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


//***********work in progress******
void Boid::view(std::vector<Boid> boids)
{
    float lineOfSight = 500;
    float viewAngle = M_PI/4;

    std::vector<Boid>::iterator it;

    PVector steer(0.0,0.0);
    int count = 500;
    PVector pos(0.0,0.0);

    for(it=boids.begin(); it!=boids.end(); it++)
    {
        PVector leader_pos = boids.begin()->m_position;
        float dist = m_position.dist(m_position, pos);
        if(dist>0.1)
        {
            steer=seek(pos);
            steer-=m_velocity;
            //steer.limit(m_maxforce);
            applyForce(steer);

        }
        //count++;
    }
}
//******end




