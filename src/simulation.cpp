#include "../include/simulation.h"

std::vector<Point> generatePoints(int points)
{

    std::vector<Point> originalPoints;

    for (int i = 0; i < points; i++)
    {

        std::cout << "Point #" << i + 1 << "\n----------\n";
        std::cout << "X: ";

        int xVal;

        std::cin >> xVal;

        std::cout << "Y: ";

        int yVal;

        std::cin >> yVal;

        originalPoints.emplace_back(xVal, yVal);
    }

    std::cout << "Points added successfully" << std::endl;
    return originalPoints;
}

double requestCurvature()
{

    double curvatureValues[] = { 0.98, 0.70, 0.50, 0.20 };

    std::cout << "Which curvature amount would you like?" << std::endl;

    for (int i = 0; i < sizeof(curvatureValues) / sizeof(*curvatureValues); i++)
    {

        std::cout << i + 1 << ". " << curvatureValues[i] * 100 << "%" << std::endl;
    }

    int response;

    std::cin >> response;

    std::cout << curvatureValues[response - 1] * 100 << "%"
        << " selected" << std::endl;

    return curvatureValues[response - 1];
}

Robot computeMovement(double leftV, double rightV, Robot currentPos, int dt)
{

    double x = currentPos.x;
    double y = currentPos.y;
    double theta = currentPos.heading;
    double trackWidth = 16; //inches

    double changeInHeading = ((rightV - leftV) / trackWidth) * (dt / 1000.0);

    double dc = (leftV + rightV) / 2 * (dt / 1000.0);

    Robot newPos(0, 0);

    newPos.y = (y + dc * sin(theta));
    newPos.x = (x + dc * cos(theta));

    newPos.heading = theta + changeInHeading;
    RateLimiter rateLimiter(50);
    newPos.leftVelocity = rateLimiter.limit(leftV, dt);
    newPos.rightVelocity = rateLimiter.limit(rightV, dt);

    return newPos;
}

//todo this is scuffed

bool shouldContinue(const std::string& response) {

    if (response != "y") {

        if (response == "n") { //todo handler positive response
            
            std::cout << "\nInput of '" << "n" << "' received" << std::endl;
            std::cout << "Exiting program ..." << std::endl;
            return false;

        }

        else {

            std::cout << "Invalid input" << std::endl;
            return shouldContinue(response);

        }
    }


    else {

        std::cout << "\nInput of '" << "y" << "' received" << std::endl;
        return true;

    }

}