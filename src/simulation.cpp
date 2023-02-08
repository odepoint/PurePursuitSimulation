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

        originalPoints.push_back(Point(xVal, yVal));
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

Robot computeMovement(double leftV, double rightV, Robot currentPos, double dt)
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
    newPos.leftVelocity = leftV;
    newPos.rightVelocity = rightV;

    return newPos;
}


std::string shouldContinue(std::string response) {


    std::string lowerCaseResponse;

    for (int i = 0; i < response.length(); i++) {

        if(response[i] != ' '){

            char lower = response.at(i);
            lower = (tolower(lower));
            lowerCaseResponse += lower;

        }

    }



    if (lowerCaseResponse != "y" && lowerCaseResponse != "yes" && lowerCaseResponse != "yeah") {

        if (lowerCaseResponse == "n" || lowerCaseResponse == "no" || lowerCaseResponse == "nope") {
            
            
            std::cout << "\nInput of '" << "n" << "' received" << std::endl;
            std::cout << "Exiting program ..." << std::endl;
            return "exit";

        }

        else {

            std::cout << "Invalid input" << std::endl;
            return "invalid";
        }
    }


    else {


        std::cout << "\nInput of '" << "y" << "' received" << std::endl;
        return "continue";

    }










}