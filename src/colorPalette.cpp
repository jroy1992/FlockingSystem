#include "colorPalette.h"
#include<vector>

colorPalette::colorPalette(Target _tar, int num)
{
    for(size_t i=0; i<num; i++)
        m_targets.push_back(_tar);
}

void colorPalette::changeColor(Target _tar, unsigned char _r, unsigned char _g, unsigned char _b)
{
    _r = _tar.getR();
    _g = _tar.getG();
    _b = _tar.getB();
}

void colorPalette::addTarget(Target _tar, int num)
{
    for(size_t i=0; i<num; i++)
        m_targets.push_back(_tar);
}
