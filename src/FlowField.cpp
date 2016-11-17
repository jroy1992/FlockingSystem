#include"FlowField.h"
#include "PVector.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"Boid.h"

int FlowField::constrain(int amt, int low, int high)
{
    if (amt < low)
    {

    }
}
void FlowField::init(int width, int height)
{
    float xoff = 0;
    for (int i = 0; i < width; i++)
    {
        float yoff = 0;
        for (int j = 0; j < height; j++)
        {
            float theta = 2*M_PI; //map(noise(xoff, yoff), 0, 1, 0, 2 * M_PI);
        }
    }
}

PVector FlowField::lookup(PVector lookup)
{
    int col = constrain(position.getX / resolution, 0, columns - 1);
    int row = constrain(lookup.getY / resolution, 0, rows - 1);
    return grid[columns][rows];
}
