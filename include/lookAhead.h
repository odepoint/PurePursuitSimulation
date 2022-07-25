#ifndef _LookAhead_h
#define _LookAhead_h

#include "pointCreation.h"
#include "robot.h"

class LookAhead
{
private:
    Point intersectionPoint;
    double intersectionIndex;
    double lookAheadDistance;

public:
    LookAhead(double inputIntersectionIndex = 0)
    {
        intersectionPoint = Point(0, 0);
        intersectionIndex = inputIntersectionIndex;
        lookAheadDistance = 18.5; //12-25
    }

    void update(std::vector<Point>& path, Robot robotPosition)

    {

        for (int i = intersectionIndex; i < path.size() - 1; i++)
        {

            Point E = path[i];
            Point L = path[i + 1];
            Point C(robotPosition.x, robotPosition.y);
            double r = lookAheadDistance;
            Point d = E.pointDiff(L);
            Point f = C.pointDiff(E);

            double a = dotProduct(d, d);

            double b = 2 * dotProduct(f, d);

            double c = dotProduct(f, f) - r * r;

            double discriminant = b * b - 4 * a * c;

            double finalT = -1;
            if (discriminant < 0)
            {

            }

            else
            {

                discriminant = sqrt(discriminant);
                double t1 = (-b - discriminant) / (2 * a);
                double t2 = (-b + discriminant) / (2 * a);

                if (t1 >= 0 && t1 <= 1)
                {
                    finalT = t1;
                }
                else if (t2 >= 0 && t2 <= 1)
                {
                    finalT = t2;
                }

            }

            if (finalT >= 0)
            {

                intersectionPoint = Point(d.x * finalT, d.y * finalT);
                intersectionPoint.x += E.x;
                intersectionPoint.y += E.y;
                intersectionIndex = i;
                break;
            }
        }
    }

    Point getIntersectionPoint()
    {

        return intersectionPoint;
    }

    double getLookAheadDistance()
    {
        return lookAheadDistance;
    }
};


#endif