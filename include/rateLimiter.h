#ifndef _RateLimiter_h
#define _RateLimiter_h

struct RateLimiter
{

    double previousOutput;
    double timeRan;
    double maxRate;
    double output = 0;

    RateLimiter(double inputMaxRate)
    {

        maxRate = inputMaxRate;
    };

    double limit(double input, double time)
    {

        double timeDiff = time - timeRan;

        double constrainedValue = 0;

        double maxChange = timeDiff * maxRate;

        if (input - previousOutput > maxChange)
            constrainedValue = maxChange;

        else if (input - previousOutput < -maxChange)
            constrainedValue = -maxChange;

        else
            constrainedValue = input - previousOutput;

        output += constrainedValue;

        previousOutput = output;
        timeRan = time;

        return output;
    }
};

#endif