#ifndef COLORPALETTE _H_
#define COLORPALETTE _H_
#include "Target.h"
#include<vector>

class colorPalette
{
public:
    colorPalette(Target _tar, int num);

    void changeColor(Target _tar, unsigned char _r, unsigned char _g, unsigned char _b);

    void addTarget(Target _tar, int num);

private:
    std::vector<Target> m_targets;
};

#endif
