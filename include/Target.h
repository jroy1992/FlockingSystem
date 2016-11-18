#ifndef TARGET_H_
#define TARGET_H_
#include "PVector.h"

class Target
{
public:
    Target() {}

    Target(PVector _pos, unsigned char _r, unsigned char _g, unsigned char _b)
    {
        m_tposition = _pos;
        m_tr = _r;
        m_tg = _g;
        m_tb = _b;
    }

    void setTColor(unsigned char _r, unsigned char _g, unsigned char _b);

    void changePosition(PVector _newPos);

    unsigned char getR() const;
    unsigned char getG() const;
    unsigned char getB() const;

private:
    float m_tsize;
    PVector m_tposition;
    unsigned char m_tr;
    unsigned char m_tg;
    unsigned char m_tb;
    int m_tboundary;
};

#endif
