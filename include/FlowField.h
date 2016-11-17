#ifndef FLOWFIELD_H
#define FLOWFIELD_H
#include"PVector.h"
#include"Boid.h"

class FlowField
{
protected:
    int rows;
    int columns;
    int resolution;
  //  PVector grid[columns][rows];
public:
    FlowField(int r, int width, int height)
    {
        resolution = r;
        columns = width / resolution;
        rows = height / resolution;
      //  grid = new PVector[columns][rows];
    }

    void init(int width, int height);
    int constrain(int, int, int);
    PVector lookup(PVector);
};
#endif
