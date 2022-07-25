#include "../include/pointCreation.h"

std::vector<Point> smoother(const std::vector<Point> &path, double weight_data, double weight_smooth, double tolerance)
{

    std::vector<std::vector<double>> newPath;
    std::vector<std::vector<double>> incomingPath;

    for (auto & i : path)
    {

        std::vector<double> point = { i.x, i.y };

        newPath.push_back(point);
        incomingPath.push_back(point);
    }

    double change = tolerance;
    while (change >= tolerance)
    {
        change = 0.0;
        for (int i = 1; i < incomingPath.size() - 1; i++)
            for (int j = 0; j < incomingPath[i].size(); j++)
            {
                double aux = newPath[i][j];
                newPath[i][j] += weight_data * (incomingPath[i][j] - newPath[i][j]) +
                    weight_smooth * (newPath[i - 1][j] + newPath[i + 1][j] -
                        (2.0 * newPath[i][j]));
                change += fabs(aux - newPath[i][j]);
            }
    }

    std::vector<Point> transformed;

    for (auto & i : newPath)
    {

        Point newPoint(i[0], i[1]);
        transformed.push_back(newPoint);
    }

    return transformed;
}

std::vector<Point> addPoints(std::vector<Point> originalPoints)
{

    std::vector<Point> newPoints;

    int spacing = 6;

    for (int i = 1; i < originalPoints.size(); i++)
    {

        double difference_y = (originalPoints[i].y - originalPoints[i - 1].y);
        double difference_x = (originalPoints[i].x - originalPoints[i - 1].x);

        double magnitude = sqrt((difference_x * difference_x) + (difference_y * difference_y));

        double num_points_that_fit = ceil(magnitude / spacing);

        double normal_x = difference_x / magnitude;

        double normal_y = difference_y / magnitude;

        for (int j = 0; j < num_points_that_fit; j++)
        {

            Point newPoint(originalPoints[i - 1].x + normal_x * spacing * j, originalPoints[i - 1].y + normal_y * spacing * j);
            newPoints.push_back(newPoint);
        }
    }

    Point newPoint(originalPoints[originalPoints.size() - 1]);
    newPoints.push_back(newPoint);

    return newPoints;
}
