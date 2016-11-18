#include "Target.h"

void Target::setTColor(unsigned char _r, unsigned char _g, unsigned char _b)
{
    m_tr = _r;
    m_tg = _g;
    m_tb = _b;
}

void Target::changePosition(PVector _newPos)
{
    m_tposition = _newPos;
}

unsigned char Target::getR()const
{
    return m_tr;
}

unsigned char Target::getG()const
{
    return m_tg;
}

unsigned char Target::getB()const
{
    return m_tb;
}
