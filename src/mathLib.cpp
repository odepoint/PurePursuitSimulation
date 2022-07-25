#include "../include/mathLib.h"


double distance_formula(Point pointNew, Point pointOld)
{

    return sqrt(pow(pointNew.x - pointOld.x, 2) + pow(pointNew.y - pointOld.y, 2));
}

double dotProduct(Point a, Point b)
{

    return (a.x * b.x + a.y * b.y);
}

static double radians(double degrees)
{
    return degrees * M_PI / 180;
}

